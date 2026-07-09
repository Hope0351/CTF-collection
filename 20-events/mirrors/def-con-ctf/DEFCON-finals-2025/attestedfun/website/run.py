from app import create_app, db, bcrypt
from app.models import User
import json

app = create_app()


def add_predefined_users():
    with open("/app/creds.json", "r") as fp:
        predefined_users = json.load(fp)

    for user_name,(user_id, hashed_password) in predefined_users.items():
        user = User(username=user_name, userid=user_id, password=hashed_password)
        if not User.query.filter_by(username=user_name).first():
            db.session.add(user)
    db.session.commit()

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
        add_predefined_users()
    app.run(host='0.0.0.0', port=5000, debug=False)
