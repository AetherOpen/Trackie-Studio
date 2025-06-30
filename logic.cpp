// logic.cpp
#include <iostream>
#include <string>
#include <emscripten.h>

// extern "C" impede a "deformação" de nomes do C++, garantindo que o nome da função
// seja exatamente 'process_text_command' no módulo WASM final, facilitando a chamada pelo JS.
extern "C" {

// EMSCRIPTEN_KEEPALIVE diz ao compilador para não remover esta função durante a otimização,
// pois ela será chamada externamente (pelo nosso JavaScript).
EMSCRIPTEN_KEEPALIVE
const char* process_text_command(const char* input_prompt) {
    // Converte a string C de entrada para uma std::string do C++ para manipulação segura.
    std::string prompt(input_prompt);
    std::string response_text;

    std::cout << "[WASM/C++] Comando recebido: " << prompt << std::endl;

    // Simula uma lógica de processamento de comandos.
    if (prompt == "GET_STATUS") {
        response_text = "STATUS_OK;TrackieLLM_v1.0;Ready";
    } else if (prompt.find("PROCESS_DATA") != std::string::npos) {
        response_text = "PROCESSING_DATA;Task_ID_12345";
    } else {
        response_text = "UNKNOWN_COMMAND";
    }

    // --- Gerenciamento de Memória Crucial ---
    // Não podemos simplesmente retornar response_text.c_str(), pois a memória de 'response_text'
    // será liberada ao final desta função, criando um ponteiro inválido (dangling pointer).
    // Precisamos alocar memória no heap do WASM que persistirá após o retorno da função.
    // O JavaScript será responsável por ler desta memória e depois liberá-la.
    char* response_buffer = new char[response_text.length() + 1];
    strcpy(response_buffer, response_text.c_str());

    return response_buffer;
}

// Esta função é essencial para evitar vazamentos de memória.
// O JavaScript chamará esta função para liberar a memória que alocamos em 'process_text_command'.
EMSCRIPTEN_KEEPALIVE
void free_memory(char* ptr) {
    delete[] ptr;
}

} // extern "C"