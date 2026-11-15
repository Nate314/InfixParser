# Compiles the C++ sources with g++, then runs the program once: it evaluates
# the sample expression in Main.cpp, prints the result and exits.
FROM gcc:14 AS build
WORKDIR /src
COPY *.cpp *.h ./
RUN g++ -std=c++17 -O2 -static -o infix *.cpp

FROM debian:bookworm-slim
COPY --from=build /src/infix /usr/local/bin/infix
CMD ["infix"]
