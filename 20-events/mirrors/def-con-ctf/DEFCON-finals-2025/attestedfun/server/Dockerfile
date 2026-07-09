# Use an official Python runtime as the base image
FROM python:3.9-slim

# Set environment variables
ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1

# Set the timezone
RUN apt-get update && apt-get install -y tzdata
ENV TZ=America/New_York

RUN apt-get install -y strace
RUN pip install pycryptodome

# Set the working directory in the container
WORKDIR /app
RUN mkdir /app/submissions/
RUN mkdir /app/output/
RUN mkdir /app/results/
RUN chmod -R 777 /app


# Copy the rest of the application code into the container
COPY attestedfun .
COPY hmacsecret.key .
COPY pi.json .
COPY test_submissions.py .
COPY start_in_docker.sh .



