FROM --platform=amd64 ico:latest as service


FROM ubuntu:24.04 AS poller

# Install required system packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    python3-dev \
    git \
    libssl-dev \
    libffi-dev \
    build-essential \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install required Python packages
RUN python3 -m pip install --upgrade pwntools --break-system-packages

# Set up poller
WORKDIR /opt
COPY poller.py .
COPY nautpolling.py .
COPY tests/ ./tests/
#COPY ./example_flag.txt /flag

# Copy the built binary from the service image
COPY --from=service /app/ico ./ico

CMD ["python3", "/opt/poller.py"]
