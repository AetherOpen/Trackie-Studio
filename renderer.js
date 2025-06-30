// renderer.js

// Executa o script quando o conteúdo do DOM estiver totalmente carregado
window.addEventListener('DOMContentLoaded', () => {

    // --- Seletores de Elementos ---
    const executionModeSelect = document.getElementById('execution-mode');
    const btnInternet = document.getElementById('btn-internet');
    const btnNightVision = document.getElementById('btn-night-vision');
    const spotwayModuleButton = document.querySelector('.module-button:nth-child(2)'); // Botão Spotway

    // Botões que dependem da câmera
    const cameraButtons = [
        document.getElementById('btn-object-viewer'),
        document.getElementById('btn-distance'),
        document.getElementById('btn-camera-feed'),
        document.getElementById('btn-segmentation'),
        document.getElementById('btn-navigation')
    ];

    // Elementos da barra lateral esquerda
    const sidebarLeft = document.querySelector('.sidebar-left');
    const collapseButton = document.querySelector('.left-toolbar .icon[title="Recolher Barra Lateral"]');


    // --- Estado da Aplicação (Simulado) ---
    let isSpotwayActive = false; // Simula se o módulo Spotway está ativo
    let isCameraActive = false;  // Simula se a câmera está ativa


    // --- Funções de Lógica ---

    /**
     * Atualiza o estado (habilitado/desabilitado) dos botões na área central
     * com base nas seleções e estados atuais.
     */
    function updateButtonStates() {
        const selectedMode = executionModeSelect.value;

        // 1. Botão "Pesquisar na Internet"
        // Habilitado apenas para TrackieIntelligence
        btnInternet.disabled = (selectedMode !== 'intelligence');

        // 2. Botão "Night Vision"
        // Habilitado apenas se o módulo Spotway estiver ativo
        btnNightVision.disabled = !isSpotwayActive;

        // 3. Botões da Câmera
        // Habilitados apenas se a câmera estiver ativa
        cameraButtons.forEach(button => {
            button.disabled = !isCameraActive;
        });
    }

    /**
     * Alterna a visibilidade da barra lateral esquerda.
     */
    function toggleSidebar() {
        sidebarLeft.classList.toggle('collapsed');
        // Altera o ícone para indicar a ação (expandir/recolher)
        if (sidebarLeft.classList.contains('collapsed')) {
            collapseButton.textContent = '➡️';
            collapseButton.title = 'Expandir Barra Lateral';
        } else {
            collapseButton.textContent = '⬅️';
            collapseButton.title = 'Recolher Barra Lateral';
        }
    }


    // --- Event Listeners ---

    // Atualiza os botões quando o modo de execução muda
    executionModeSelect.addEventListener('change', updateButtonStates);

    // Recolhe/expande a barra lateral
    collapseButton.addEventListener('click', toggleSidebar);

    // Simula a ativação/desativação do Spotway para teste
    spotwayModuleButton.addEventListener('click', () => {
        isSpotwayActive = !isSpotwayActive;
        spotwayModuleButton.style.border = isSpotwayActive ? '1px solid #4CAF50' : '1px solid #4A5052';
        console.log(`Spotway Ativo: ${isSpotwayActive}`);
        updateButtonStates(); // Reavalia o estado dos botões
    });


    // --- Inicialização ---

    // Define o estado inicial correto dos botões ao carregar a página
    updateButtonStates();

    // Log para confirmar que o script foi carregado
    console.log('Renderer script loaded and running.');
    console.log('Estado inicial: Câmera Desativada, Spotway Desativado. Mude o dropdown "Configurações de Execução" para ver a reatividade.');

});