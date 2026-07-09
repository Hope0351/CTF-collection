FROM --platform=amd64 ubuntu:24.04 AS build

# Install required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    fp-compiler \
    fp-units-base \
    fp-units-fcl \
    fp-units-gfx \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Copy source and test artifacts
WORKDIR /app
COPY service/ .
COPY tests/ ./tests/

# Compile the service and unit tests
# See: https://www.freepascal.org/docs-html/user/userap1.html
#RUN fpc -vh -Sd -Un -Cg -Cr- -gw -O- -Px86_64 -dDEBUG -oico_test test.pas
RUN fpc -vh -Sd -Un -Cg -Cr- -Co- -gw -O- -Px86_64 -oico_test test.pas
#RUN fpc -vh -Sd -Un -Cg -Cr- -gw -O- -Px86_64 -dDEBUG -oico ico.pas
RUN fpc -vh -Sd -Un -Cg -Cr- -Co- -O3 -Px86_64 -oico ico.pas

# Run the test files through the test application and make sure nothing crashes
RUN for file in /app/tests/*.hvif; do \
        echo "Testing: $file"; \
        /app/ico_test "$file" || exit 1; \
    done

# Run the files we generated through the test application, too, for good measure
RUN for file in /app/tests/*_copy.hvif; do \
        echo "Re-testing: $file"; \
        /app/ico_test "$file" || exit 1; \
        omd5=$(md5sum "$file" | awk '{print $1}'); \
        nfile="${file%_copy.hvif}_copy_copy.hvif"; \
        nmd5=$(md5sum "$nfile" | awk '{print $1}'); \
        if [ "$omd5" != "$nmd5" ]; then \
            echo "ERROR: Mismatch between $file and $nfile"; \
            exit 1; \
        fi; \
    done


FROM --platform=amd64 ubuntu:24.04

# Install required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    adduser \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up application
WORKDIR /app
COPY --from=build /app/ico ./ico
RUN chmod 755 ./ico

# Add unprivileged user for service
RUN adduser --no-create-home --disabled-password --gecos "" ico

CMD ["/app/ico"]
