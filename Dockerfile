FROM node:22-bullseye

# Install g++
RUN apt-get update && apt-get install -y g++

WORKDIR /app

COPY package*.json ./
RUN npm install

COPY . .

# compile C++ -> Linux binary
RUN g++ calc.cpp -o calc

EXPOSE 3000

CMD ["node", "server.js"]
