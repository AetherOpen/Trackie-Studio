// main.js

// Módulos para controlar o ciclo de vida da aplicação e criar janela nativa do navegador
const { app, BrowserWindow } = require('electron');
const path = require('path');

// Função para criar a janela da aplicação
const createWindow = () => {
    // Cria a janela do navegador.
    const mainWindow = new BrowserWindow({
        width: 1200,
        height: 800,
        minWidth: 940,
        minHeight: 600,
        backgroundColor: '#1C2526',
        title: 'TrackieApp',
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'), // Usaremos mais tarde para comunicação segura
            nodeIntegration: false,
            contextIsolation: true,
        }
    });

    // e carrega o index.html do aplicativo.
    mainWindow.loadFile('index.html');

    // Abre o DevTools (ferramentas de desenvolvedor) - útil para depuração.
    // mainWindow.webContents.openDevTools();
};

// Este método será chamado quando o Electron tiver finalizado
// a inicialização e estiver pronto para criar janelas do navegador.
// Algumas APIs podem ser usadas somente após a ocorrência deste evento.
app.whenReady().then(() => {
    createWindow();

    app.on('activate', () => {
        // No macOS, é comum recriar uma janela no aplicativo quando o
        // ícone do dock é clicado e não há outras janelas abertas.
        if (BrowserWindow.getAllWindows().length === 0) {
            createWindow();
        }
    });
});

// Saia quando todas as janelas estiverem fechadas, exceto no macOS. Lá, é comum
// para aplicativos e sua barra de menu permanecerem ativos até que o usuário saia
// explicitamente com Cmd + Q.
app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});

// Neste arquivo, você pode incluir o resto do código do processo principal do seu
// aplicativo. Você também pode colocar eles em arquivos separados e requerê-los aqui.