FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN make

ENTRYPOINT ["./t3c"]
