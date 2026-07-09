# Use an official Python runtime as the base image
FROM python:3.9-slim

# Set environment variables
ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1

# Set the timezone
RUN apt-get update && apt-get install -y tzdata
ENV TZ=America/New_York

RUN apt-get install -y strace

# Set the working directory in the container
WORKDIR /app

# Copy the requirements file into the container
COPY requirements.txt .

# Install the required packages
RUN pip install --no-cache-dir -r requirements.txt

# Copy the rest of the application code into the container
COPY . .

RUN chmod -R 777 /app/app

# Expose the port the app runs on
EXPOSE 80

# Run the application
CMD ["python", "run.py"]


