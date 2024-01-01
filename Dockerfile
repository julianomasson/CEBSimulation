# Use uma imagem oficial do Ubuntu 16.04 como imagem base
FROM n0madic/alpine-gcc:10.4.0

# Atualize as listas de pacotes e instale os pacotes necessários
RUN apk --no-cache add cmake clang clang-dev make gcc g++ libc-dev linux-headers

# Copie o conteúdo do diretório atual para o contêiner em /CEBSimulation
COPY . /CEBSimulation

# Defina o diretório de trabalho como /CEBSimulation
WORKDIR /CEBSimulation

# Crie um diretório de compilação, configure com o cmake, compile o projeto e instale-o
RUN mkdir build2 && \
    cmake . -B ./build2 && \
    cmake --build ./build2 --config Release

# Defina o ponto de entrada (entrypoint) para o contêiner
#ENTRYPOINT ["./build2/CEBSimulation", "--input", "configuration.json"]
