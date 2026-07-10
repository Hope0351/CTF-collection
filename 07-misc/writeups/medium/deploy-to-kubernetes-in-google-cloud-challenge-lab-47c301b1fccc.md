# :game_die: Deploy to Kubernetes in Google Cloud: Challenge Lab

---

*you can find your project id here*

## TASK 1: Create a Docker image and store the Dockerfile

## Solution

We need to run this command `source <(gsutil cat gs://cloud-training/gsp318/marking/setup_marking.sh)` it install the script required for google to check our progress

Now we need to run this command to clone the task files from github `gcloud source repos clone valkyrie-app --project={put your project id here}`
(Don't forget to put your project id)

Now we will go to the valkyrie-app directory `cd valkyrie-app` and create a docker file with this command `cat > Dockerfile <<EOF`

and we will paste the configuration given in the task instructions:

```
FROM golang:1.10
WORKDIR /go/src/app
COPY source .
RUN go install -v
ENTRYPOINT ["app","-single=true","-port=8080"]
EOF
```

Now build the image using this command `docker build -t valkyrie-app:v0.0.1 .`

Now we will run the script we downloaded earlier so it checks if we did everything correctly

```
cd ~/marking
./step1.sh
```

Now press `check my progress` On the lab page, it should turn green

## Solution

I used this command to change my directory to `valkyrie-app`

```
cd ..
cd valkyrie-app
```

Now we will use this command `docker run -p 8080:8080 --name valkyrie-app valkyrie-app:v0.0.1 &` to run the docker image that we built in task 1

*Now click web preview*

Now open a new cloud shell and run the script we downloaded earlier so it checks if we did everything correctly

```
cd ~/marking
./step2.sh
```

Now press `check my progress` On the lab page, it should turn green

## Solution

Now we will push the Docker image

`docker tag valkyrie-app:v0.0.1 gcr.io/{put your project id here}/valkyrie-app:v0.0.1`

(Dont forget to put your project id)

`docker images`

`docker push gcr.io/{put your project id here}/valkyrie-app:v0.0.1`

(Don't forget to put your project id)

Now press `check my progress` On the lab page, it should turn green

## Solution

First, we should be in `k8s` the directory which is inside `valkyrie-app/` by using these commands

`cd valkyrie-app/`

`cd k8s`

Get authentication credentials for the cluster by using `gcloud container clusters get-credentials valkyrie-dev --zone us-east1-d`

Now we need to edit `deployment.yaml` using `nano deployment.yaml`

Change `IMAGE_HERE` with [gcr.io/](http://gcr.io/){put your project id here}/valkyrie-app:v0.0.1

(Don't forget to put your project id)

Then press `Ctrl o` to save then press `enter` then press `Ctrl x` to exit

Now we will use:

```
kubectl create -f deployment.yaml
kubectl create -f service.yaml
```

to deploy deployment.YAML and service.YAML

Now press `check my progress` On the lab page, it should turn green

## Solution

Increase the replicas from 1 to 3

kubectl scale deployment valkyrie-dev — replicas 3

Now we go to the `valkyrie-app` directory using `cd ..`

and merge the branch called kurt-dev into master using the following git command:

`git merge origin/kurt-dev`

Now we will build and push the new version with tag `2.0.0`

`docker build -t valkyrie-app:v0.0.2 .`

`docker tag valkyrie-app:v0.0.2 gcr.io/{put your project id here}/valkyrie-app:v0.0.2`

## Get Noureldin Ehab | Creeper.exe’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

(Don't forget to put your project id)

`docker images`

`docker push gcr.io/{put your project id here}/valkyrie-app:v0.0.2`

(Don't forget to put your project id)

Change the image tags from `v0.0.1` to `v0.0.2` for the backend and frontend using:

`kubectl set image deployment valkyrie-dev backend=gcr.io/{put your project id here}/valkyrie-app:v0.0.2 frontend=gcr.io/{put your project id here}/valkyrie-app:v0.0.2`
(Don't forget to put your project id)

Now press `check my progress` in the lab page it should turn green

## Solution

To know the password run this command

`printf $(kubectl get secret cd-jenkins -o jsonpath="{.data.jenkins-admin-password}" | base64 --decode);echo`

To avoid errors later on run the following commands to kill any running containers

docker ps

docker container kill $(docker ps -aq)

Connect to the Jenkins console using the commands below:

```
export POD_NAME=$(kubectl get pods --namespace default -l "app.kubernetes.io/component=jenkins-master" -l "app.kubernetes.io/instance=cd" -o jsonpath="{.items[0].metadata.name}")
kubectl port-forward $POD_NAME 8080:8080 >> /dev/null &
```

Click on the Web Preview button in cloud shell, then click “Preview on port 8080” to connect to the Jenkins console.

username: `admin`

password: We ran this command earlier for the password `printf $(kubectl get secret cd-jenkins -o jsonpath="{.data.jenkins-admin-password}" | base64 --decode);echo`

In the Jenkins user interface, click `Manage Jenkins` in the left navigation.

In the Jenkins user interface, click `Manage Credentials` in the left navigation.

Click `Jenkins`

Click `Global credentials (unrestricted).`

Click `Add Credentials` in the left navigation.

Select `Google Service Account from metadata` from the `Kind drop-down`

click `OK`.

Go to the dashboard again and click `new item`

Name the project `valkyrie-app`, then choose the `Multibranch Pipeline` option and click `OK`.

click `Add Source`.

select `git`.

Paste the HTTPS clone URL of your sample-app repo in Cloud Source Repositories `https://source.developers.google.com/p/{put your project id here}/r/valkyrie-app` into the Project Repository field

(Don't forget to put your project id)

From the `Credentials` drop-down, select the name of the credentials you created when adding your service account in the previous steps.

Under the `Scan Multibranch Pipeline Triggers` section, check the `Periodically if not otherwise run` box and set the Interval value to `1 minute`.

Click `apply` then `save`.

nano `Jenkinsfile`.

replace `YOUR_PROJECT` with your GCP project ID

nano `source/html.go`

Commit and push the changes:

```
git config --global user.email $PROJECT
git config --global user.name $PROJECTgit add *
git commit -m 'green to orange'
git push origin master
```

Now press `check my progress` On the lab page, it should turn green

## Resources I used when I got Stuck

[chriskyfung GitHub repo](https://chriskyfung.github.io/blog/qwiklabs/deploy-to-kubernetes-in-google-cloud-challenge-lab)

## I love connecting with different people so if you want to say hi, I’ll be happy to meet you more! :)

[LinkedIn](https://www.linkedin.com/in/noureldin-ehab-a57940190/)

[Twitter](https://twitter.com/Nouureldin_Ehab)

---
