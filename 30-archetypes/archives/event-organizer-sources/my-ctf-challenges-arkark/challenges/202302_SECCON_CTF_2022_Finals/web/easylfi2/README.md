# [web] easylfi2

## Description

easylfi again! I know you fully understand everything about curl.

- `http://easylfi2.{int,dom}.seccon.games:3000`

## Attachments

- [easylfi2](files/easylfi2)

## Usage

Launch a challenge server:

```
cd build
docker compose up
```

Run the author's solver:

```
docker run -it \
    -e SECCON_HOST=localhost \
    -e SECCON_PORT=3000 \
    --network=host \
    (docker build -q ./solver)
```
