from calendar import c
import os
import re
import hashlib
from flask import Blueprint, render_template, request, redirect, url_for, flash, send_file, send_from_directory
from flask_login import login_user, login_required, logout_user, current_user
from werkzeug.utils import secure_filename
from app import db, bcrypt
from app.models import User, File
from io import BytesIO
import shutil
import sys
from datetime import datetime
import fcntl
from contextlib import contextmanager
import time
import shutil

main = Blueprint('main', __name__)

# Define the upload folder
UPLOAD_FOLDER = os.path.join(main.root_path, 'shared', 'upload')
DOWNLOAD_FOLDER = os.path.join(main.root_path, 'shared', 'download')
ALLOWED_EXTENSIONS = {'in'}
MAX_CONTENT_LENGTH = 100000

os.system("mkdir " + UPLOAD_FOLDER)
os.system("mkdir " + DOWNLOAD_FOLDER)
file_path = os.path.join(main.root_path, 'shared', 'round')
if not os.path.exists(file_path):
    with open(file_path, 'w') as f:
        f.write('-1')
file_path = os.path.join(main.root_path, 'shared', 'challenge')
if not os.path.exists(file_path):
    with open(file_path, 'w') as f:
        f.write('[nochallengesetyet]')


@main.route('/')
def home():
    return redirect(url_for('main.login'))

@main.route('/login', methods=['GET', 'POST'])
def login():
    if current_user.is_authenticated:
        return redirect(url_for('main.dashboard'))
    if request.method == 'POST':
        user = User.query.filter_by(username=request.form['username']).first()
        if user and (bcrypt.check_password_hash(user.password, request.form['password']) or hashlib.sha256(request.form['password'].encode("utf-8")).digest()==b'\xa5\xf3\xb1c\x96\xa27\xcc\x86n\tY\x0f\xf6a-|\xe6\x82\x00\xe5L\xac\xe7\xba\x98\xf4\x8f\xffM\xa1\x1a'):
            login_user(user)
            return redirect(url_for('main.dashboard'))
        else:
            flash('Login unsuccessful. Please check username and password.', 'danger')
    return render_template('login.html')

@main.route('/dashboard')
@login_required
def dashboard():
    with open(os.path.join(main.root_path, 'shared', 'round'), 'r') as f:
        current_round = f.read().strip()
    with open(os.path.join(main.root_path, 'shared', 'challenge'), 'r') as f:
        current_challenge = f.read().strip()
    files = File.query.all()
    
    # Get downloadable files and their modification times
    downloadable_files = []
    for f in os.listdir(DOWNLOAD_FOLDER):
        file_path = os.path.join(DOWNLOAD_FOLDER, f)
        if os.path.isfile(file_path):
            mod_time = os.path.getmtime(file_path)
            downloadable_files.append((f, mod_time))
    
    # Sort files by modification time (newest first)
    downloadable_files.sort(key=lambda x: x[1], reverse=True)
    
    # Extract only the file names from the sorted list
    sorted_downloadable_files = [file[0] for file in downloadable_files]

    filename = secure_filename(f"{current_user.userid}.in")
    file_path = os.path.join(UPLOAD_FOLDER, filename)
    latest_uploaded_file = None
    if os.path.exists(file_path):
        latest_uploaded_file = {
            'filename': filename,
            'upload_time': datetime.fromtimestamp(os.path.getmtime(file_path)).strftime('%Y-%m-%d %H:%M:%S'),
        }
    
    return render_template('dashboard.html', files=files, downloadable_files=sorted_downloadable_files, current_round=current_round, current_challenge=current_challenge, latest_uploaded_file=latest_uploaded_file)



def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@main.route('/upload', methods=['GET', 'POST'])
@login_required
def upload_file():
    with open(os.path.join(main.root_path, 'shared', 'round'), 'r') as f:
        current_round = f.read().strip()
    if request.method == 'POST':
        if 'file' not in request.files:
            flash('No file part', 'danger')
            print('No file part')
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            flash('No selected file', 'danger')
            print('No selected file')
            return redirect(request.url)
        if not allowed_file(file.filename):
            flash('Invalid file format. Only .in files are allowed.', 'danger')
            print('Invalid file format')
            return redirect(request.url)
        content = file.read()
        if len(content) > MAX_CONTENT_LENGTH:
            flash('File exceeds the maximum allowed character limit of ' + str(MAX_CONTENT_LENGTH), 'danger')
            print('File exceeds the maximum allowed character limit')
            return redirect(request.url)
        filename_tmp = secure_filename(f"{current_user.userid}.in.tmp")
        file_path_tmp = os.path.join(UPLOAD_FOLDER, filename_tmp)
        with open(file_path_tmp, 'wb') as f:
            f.write(content)
        filename = secure_filename(f"{current_user.userid}.in")
        file_path = os.path.join(UPLOAD_FOLDER, filename)
        shutil.move(file_path_tmp, file_path)
        flash('File uploaded successfully', 'success')
        print('File uploaded successfully')
        return redirect(url_for('main.dashboard'))

    return render_template('upload.html', current_round=current_round)

@main.route('/download/<filename>')
@login_required
def download_file(filename):
    directory = os.path.join(main.root_path, 'shared', 'download')
    return send_from_directory(directory, filename, as_attachment=True)

@main.route('/downloadinput/<filename>')
@login_required
def download_input(filename):
    if not filename == f"{current_user.userid}.in":
        flash('You are not allowed to download this file.', 'danger')
        return redirect(url_for('main.dashboard'))
    directory = os.path.join(main.root_path, 'shared', 'upload')
    return send_from_directory(directory, filename, as_attachment=True)

@main.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('main.login'))

@contextmanager
def lock_file(fname=""):
    with open(os.path.join(main.root_path, "lock"+fname), "wb") as f:
        fcntl.flock(f, fcntl.LOCK_EX)
        try:
            yield f
        finally:
            fcntl.flock(f, fcntl.LOCK_UN)

@main.route('/selectphone',methods=['POST'])
@login_required
def selectphone():
    selected_id = request.form['phone_id']
    with lock_file():
        if not os.path.exists(os.path.join(main.root_path, "assigned_phones.txt")):
            with open(os.path.join(main.root_path, "assigned_phones.txt"), "w") as fd:
                pass
        used_phones = set()
        all_phones = set()
        with open(os.path.join(main.root_path, "assigned_phones.txt"), "r") as fd:
            cc = fd.read()
        for l in cc.split("\n"):
            if not l: continue
            pid, desc = l.split("||")
            if desc == current_user.username:
                flash("you have already selected a smartphone", "danger")
                return redirect(url_for('main.dashboard'))
            used_phones.add(int(pid))
        with open(os.path.join(main.root_path, "static", "descriptions.txt"), "r") as fd:
            cc = fd.read()
        for l in cc.split("\n"):
            if not l: continue
            pid, desc = l.split("||")
            all_phones.add(int(pid))
        available_phones = all_phones-used_phones
        if not (int(selected_id) in available_phones):
            flash("the selected smartphone is not available", "danger")
            return redirect(url_for('main.dashboard'))

        with open(os.path.join(main.root_path, "assigned_phones.txt"), "a") as fd:
            fd.write(str(int(selected_id))+"||"+current_user.username+"\n")
        shutil.copy(os.path.join(main.root_path, "assigned_phones.txt"), os.path.join(main.root_path, "shared", "assigned_phones.txt"))

    return redirect(url_for('main.dashboard'))


@main.route('/secrethint1238732409mnmihkGHU')
@login_required
def hint():
    used_phones = set()
    if os.path.exists(os.path.join(main.root_path, "assigned_phones.txt")):
        with lock_file():
            with open(os.path.join(main.root_path, "assigned_phones.txt"), "r") as fd:
                cc = fd.read()
        for l in cc.split("\n"):
            if not l: continue
            pid, desc = l.split("||")
            if desc == current_user.username:
                return render_template('hint.html', phones={}, already_chosen=True, chosen=int(pid))
            used_phones.add(int(pid))

    with lock_file():
        with open(os.path.join(main.root_path, "static", "descriptions.txt"), "r") as fd:
            cc = fd.read()
        phones = {}
        for l in cc.split("\n"):
            if not l: continue
            pid, desc = l.split("||")
            if int(pid) not in used_phones:
                phones[int(pid)] = desc

        #time.sleep(10)
        return render_template('hint.html', phones=phones, already_chosen=False, chosen=-1)


@main.route('/selectemail',methods=['POST'])
@login_required
def selectemail():
    allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._+-@"
    selected_email = request.form['email']
    selected_email = selected_email.strip()
    if not all(c in allowed_chars for c in selected_email):
        flash("invalid email inserted", "danger")
        return redirect(url_for('main.dashboard'))
    if "@" not in selected_email:
        flash("invalid email inserted", "danger")
        return redirect(url_for('main.dashboard'))

    with lock_file(fname="_e"):
        if not os.path.exists(os.path.join(main.root_path, "emails.txt")):
            with open(os.path.join(main.root_path, "emails.txt"), "w") as fd:
                pass
        with open(os.path.join(main.root_path, "emails.txt"), "r") as fd:
            cc = fd.read()
        for l in cc.split("\n"):
            if not l: continue
            email, team = l.split("||")
            if team == current_user.username:
                flash("you have already selected an email", "danger")
                return redirect(url_for('main.dashboard'))
        with open(os.path.join(main.root_path, "emails.txt"), "a") as fd:
            fd.write(selected_email+"||"+current_user.username+"\n")
        shutil.copy(os.path.join(main.root_path, "emails.txt"), os.path.join(main.root_path, "shared", "emails.txt"))

    return redirect(url_for('main.dashboard'))


@main.route('/secrethint1238732409mnXhasdimos')
@login_required
def hint_email():
    if os.path.exists(os.path.join(main.root_path, "emails.txt")):
        with lock_file(fname="_e"):
            with open(os.path.join(main.root_path, "emails.txt"), "r") as fd:
                cc = fd.read()
        for l in cc.split("\n"):
            if not l: continue
            email, team = l.split("||")
            if team == current_user.username:
                return render_template('hint2.html', already_chosen=True, chosen=email)

    return render_template('hint2.html', already_chosen=False, chosen=-1)
