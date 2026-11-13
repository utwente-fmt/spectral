FROM mcr.microsoft.com/devcontainers/base:noble
# Setup for LLVM
RUN apt-get update && apt-get -y install \
        openjdk-17-jre \
        build-essential \
        libzstd-dev \
        zlib1g-dev \ 
        gdb \
        cmake \
        ninja-build \ 
        llvm-17-dev \
        clang-17

# Install venv for testing
RUN apt-get -y install python3-venv

# Setup Swift 6
# See https://www.swift.org/install/linux/tarball/
# Based on https://github.com/swiftlang/swift-docker/blob/main/6.0/ubuntu/24.04/Dockerfile

# Install dependencies 
RUN apt-get -q install -y \
        binutils \
        git \
        gnupg2 \
        libc6-dev \
        libcurl4-openssl-dev \
        libedit2 \
        libgcc-13-dev \
        libncurses-dev \
        libpython3-dev \
        libsqlite3-0 \
        libstdc++-13-dev \
        libxml2-dev \
        libz3-dev \
        pkg-config \
        tzdata \
        unzip \
        zlib1g-dev \ 
        curl
ARG SWIFT_PREFIX=/opt/swift
ARG SWIFT_SIGNING_KEY=52BB7E3DE28A71BE22EC05FFEF80A866B47A981F
ARG TARGETARCH

# Download swift & signature
RUN set -eu; \
        case "$TARGETARCH" in \
                amd64) SUFFIX="" ;; \
                arm64) SUFFIX="-aarch64" ;; \
                *) echo "Unsupported TARGETARCH"; exit 1;; \
        esac; \
        SWIFT_URL="https://download.swift.org/swift-6.0.1-release/ubuntu2404${SUFFIX}/swift-6.0.1-RELEASE/swift-6.0.1-RELEASE-ubuntu24.04${SUFFIX}.tar.gz"; \
        export GNUPGHOME="$(mktemp -d)"; \
        curl -fsSL "$SWIFT_URL" -o swift6.tar.gz "$SWIFT_URL.sig" -o swift6.tar.gz.sig; \
        gpg --quiet --keyserver hkp://keyserver.ubuntu.com --recv-keys "$SWIFT_SIGNING_KEY"; \
        gpg --verify swift6.tar.gz.sig swift6.tar.gz; \
        mkdir -p "$SWIFT_PREFIX"; \
        tar -xzf swift6.tar.gz --directory "$SWIFT_PREFIX" --strip-components=1; \
        chmod -R o+r "$SWIFT_PREFIX/usr/lib/swift"; \
        rm -rf "$GNUPGHOME" swift6.tar.gz.sig swift6.tar.gz

ENV PATH="${PATH}:${SWIFT_PREFIX}/usr/bin"