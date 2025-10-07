import cv2
import mediapipe as mp
import time as t
import pyautogui
import threading
import numpy as np
import pygame
import serial
import vlc


pygame.mixer.init() 
negro = serial.Serial('COM13', 9600, timeout = 1)
branco = serial.Serial('COM11', 9600, timeout = 1)
s = serial.Serial('COM14', 9600, timeout=1) #ARDUINOOOO

#--------ROBO_NEGRO---------------------------------------------------------------------
def enviar_olodum_negro():
    negro.write(b'N')
    data = negro.readline().decode('ascii').strip()
    return data

def enviar_criminal_negro():
    negro.write(b'S')
    data = negro.readline().decode('ascii').strip()
    return data

def enviar_thriller_negro():
    negro.write(b'T')
    data = negro.readline().decode('ascii').strip()
    return data
#----------------------------------------------------------------------------------------

#--------ROBO_BRANCO---------------------------------------------------------------------
def enviar_olodum_branco():
    branco.write(b'B')
    data = branco.readline().decode('ascii').strip()  # corrigido para 'branco' aqui
    return data

def enviar_criminal_branco():
    branco.write(b'S')
    data = branco.readline().decode('ascii').strip()
    return data

def enviar_thriller_branco():
    branco.write(b'T')
    data = branco.readline().decode('ascii').strip()
    return data
#-----------------------------------------------------------------------------

#--------LEDS_JUKBOXXXXXX-----------------------------------------------------
def enviar_criminal_ardu():
    s.write(b'G')
    data = s.readline().decode('ascii').strip()
    return data

def enviar_olodum_ardu():
    s.write(b'O')
    data = s.readline().decode('ascii').strip()
    return data

def enviar_thriller_ardu():
    s.write(b'T')
    data = s.readline().decode('ascii').strip()
    return data
#-------------------------------------------------------------

musica_criminal = r"C:\Users\gabri\Downloads\Michael Jackson - Smooth Criminal (Single Version) HD (1).mp3"
musica_olodum = r"C:\Users\gabri\Downloads\Michael Jackson - They Don’t Care About Us (Brazil Version) (Official Video) (1).mp3"
musica_thriller = r"C:\Users\gabri\Downloads\Michael Jackson The Experience Thriller (1) (2).mp3"

TEMPO_ENTRE_GESTOS = 5

mp_pose = mp.solutions.pose
pose = mp_pose.Pose()
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(max_num_hands=1)
mp_drawing = mp.solutions.drawing_utils

button_coords = [(50, 400), (250, 400), (450, 400)]
BUTTON_WIDTH, BUTTON_HEIGHT = 150, 50
CAM_WIDTH, CAM_HEIGHT = 250, 250
VIDEO_WIDTH, VIDEO_HEIGHT = 640, 360

cap = cv2.VideoCapture(0)
def interface():
    # Carrega a imagem de fundo (PNG ou JPG)
    background = cv2.imread(r"C:\Users\gabri\OneDrive\Documentos\GDA.png", cv2.IMREAD_UNCHANGED)
    if background is None:
        print("⚠️ Erro: fundo.png não encontrado, usando branco como fallback.")
        background = 255 * np.ones((VIDEO_HEIGHT + 100, VIDEO_WIDTH, 3), dtype=np.uint8)
    else:
        background = cv2.resize(background, (VIDEO_WIDTH, VIDEO_HEIGHT + 100))

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        frame = cv2.flip(frame, 1)
        frame = cv2.rotate(frame, cv2.ROTATE_90_CLOCKWISE)
        cam_frame = cv2.resize(frame, (CAM_WIDTH, CAM_HEIGHT))

        # Copia o fundo para desenhar por cima
        if background.shape[2] == 4:  # PNG com alpha
            alpha = background[:, :, 3] / 255.0
            rgb_bg = background[:, :, :3]
            interface_frame = np.zeros((VIDEO_HEIGHT + 100, VIDEO_WIDTH, 3), dtype=np.uint8)
            for c in range(3):
                interface_frame[:, :, c] = (alpha * rgb_bg[:, :, c] + (1 - alpha) * 255).astype(np.uint8)
        else:
            interface_frame = background.copy()

        # Posiciona a câmera no canto superior direito
        top_y = 0
        top_x = VIDEO_WIDTH - CAM_WIDTH
        interface_frame[top_y:top_y+CAM_HEIGHT, top_x:top_x+CAM_WIDTH] = cam_frame

        # Processa pose e mãos
        rgb = cv2.cvtColor(cam_frame, cv2.COLOR_BGR2RGB)
        results_pose = pose.process(rgb)
        results_hands = hands.process(rgb)

        if results_pose.pose_landmarks:
            mp_drawing.draw_landmarks(
                interface_frame[top_y:top_y+CAM_HEIGHT, top_x:top_x+CAM_WIDTH],
                results_pose.pose_landmarks, mp_pose.POSE_CONNECTIONS
            )

        if results_hands.multi_hand_landmarks:
            for hand_landmarks in results_hands.multi_hand_landmarks:
                mp_drawing.draw_landmarks(
                    interface_frame[top_y:top_y+CAM_HEIGHT, top_x:top_x+CAM_WIDTH],
                    hand_landmarks, mp_hands.HAND_CONNECTIONS
                )

        # Desenha botões
        for i, (x, y) in enumerate(button_coords):
            cv2.rectangle(interface_frame, (x, y), (x + BUTTON_WIDTH, y + BUTTON_HEIGHT), (0, 255, 0), -1)
            cv2.putText(interface_frame, f"Play {i+1}", (x + 20, y + 30),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 0), 2)

        # Tela fullscreen
        cv2.namedWindow("Interface", cv2.WND_PROP_FULLSCREEN)
        cv2.setWindowProperty("Interface", cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
        cv2.imshow("Interface", interface_frame)

        if cv2.waitKey(1) & 0xFF == 27:  # Esc sai
            break

    cv2.destroyAllWindows()



player = None
monitor_thread = None

def monitorar_player():
    global player
    while player is not None:
        estado = player.get_state()
        if estado in [vlc.State.Ended, vlc.State.Error, vlc.State.Stopped]:
            player.stop()
            print("✅ Vídeo finalizado. Player parado.")
            break
        t.sleep(0.1)

def tocar_video(index):
    global player, monitor_thread
    if player is not None:
        player.stop()
        player = None

    if index == 0:
        video_path = r"C:\Users\gabri\OneDrive\Documentos\Smooth Crimininal part2.mp4"
        enviar_criminal_ardu()
        enviar_criminal_branco()
        enviar_criminal_negro()
    elif index == 1:
        video_path = r"C:\Users\gabri\OneDrive\Documentos\Olodum.mp4"
        enviar_olodum_ardu()
        enviar_olodum_branco()
        enviar_olodum_negro()
    elif index == 2:
        video_path = r"C:\Users\gabri\OneDrive\Documentos\thriller.mp4"
        enviar_thriller_ardu()
        enviar_thriller_branco()
        enviar_thriller_negro()
    else:
        return

    instance = vlc.Instance()
    player = instance.media_player_new()
    media = instance.media_new(video_path)
    player.set_media(media)
    player.play()

    # Iniciar thread que monitora o fim do vídeo
    #if monitor_thread is not None and monitor_thread.is_alive():
        #monitor_thread.join()
    monitor_thread = threading.Thread(target=monitorar_player, daemon=True)
    monitor_thread.start()

def acionar_video(index):
    x, y = 212, 705
    a, b = 661, 705
    z, w = 1080, 705
    if index == 0:
        pyautogui.click(x + 10, y + 10)
        tocar_video(0)
    elif index == 1:
        pyautogui.click(a + 10, b + 10)
        tocar_video(1)
    elif index == 2:
        pyautogui.click(z + 10, w + 10)
        tocar_video(2)

def detectar_levantar_braco():
    print("🕺 Levante o braço esquerdo acima do ombro...")
    cont_frames_validos = 0
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        frame = cv2.flip(frame, 1)
        frame = cv2.rotate(frame, cv2.ROTATE_90_CLOCKWISE)
        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = pose.process(rgb)

        if results.pose_landmarks:
            lm = results.pose_landmarks.landmark
            if lm[mp_pose.PoseLandmark.RIGHT_WRIST].visibility < 0.5:
                continue

            ombro = lm[mp_pose.PoseLandmark.RIGHT_SHOULDER]
            cotovelo = lm[mp_pose.PoseLandmark.RIGHT_ELBOW]
            punho = lm[mp_pose.PoseLandmark.RIGHT_WRIST]

            if punho.y < ombro.y and cotovelo.y < ombro.y:
                cont_frames_validos += 1
            else:
                cont_frames_validos = 0

            if cont_frames_validos >= 10:
                print("✅ Braço levantado detectado")
                acionar_video(0)
                return

def movimento_levantar_abaixar():
    print("🎯 Levante e abaixe o braço direito...")
    estado = "esperando_abaixado"
    cont_frames = 0
    tolerancia_frames = 6
    historico_punho_y = []

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        frame = cv2.flip(frame, 1)
        frame = cv2.rotate(frame, cv2.ROTATE_90_CLOCKWISE)
        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = pose.process(rgb)

        if results.pose_landmarks:
            lm = results.pose_landmarks.landmark
            ombro = lm[mp_pose.PoseLandmark.RIGHT_SHOULDER]
            punho = lm[mp_pose.PoseLandmark.RIGHT_WRIST]

            if punho.visibility < 0.6 or ombro.visibility < 0.6:
                continue

            historico_punho_y.append(punho.y)
            if len(historico_punho_y) > 5:
                historico_punho_y.pop(0)
            media_punho_y = np.mean(historico_punho_y)

            if estado == "esperando_abaixado" and media_punho_y > ombro.y + 0.05:
                cont_frames += 1
                if cont_frames >= tolerancia_frames:
                    estado = "levantando"
                    cont_frames = 0
                    print("⬇️ Braço abaixado detectado")

            elif estado == "levantando" and media_punho_y < ombro.y - 0.05:
                cont_frames += 1
                if cont_frames >= tolerancia_frames:
                    estado = "abaixando_novamente"
                    cont_frames = 0
                    print("⬆️ Braço levantado detectado")

            elif estado == "abaixando_novamente" and media_punho_y > ombro.y + 0.05:
                cont_frames += 1
                if cont_frames >= tolerancia_frames:
                    print("🔁 Movimento completo detectado!")
                    acionar_video(1)
                    return
            else:
                cont_frames = 0

def esperar_dois_bracos_levantados():
    print("🙌 Levante os dois braços acima dos ombros para continuar...")

    frames_validos = 0
    tolerancia_frames = 8  # quantos frames seguidos precisa manter a pose

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        frame = cv2.flip(frame, 1)
        frame = cv2.rotate(frame, cv2.ROTATE_90_CLOCKWISE)
        rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = pose.process(rgb)

        if results.pose_landmarks:
            lm = results.pose_landmarks.landmark

            # Coordenadas dos ombros e punhos
            ombro_dir = lm[mp_pose.PoseLandmark.RIGHT_SHOULDER]
            ombro_esq = lm[mp_pose.PoseLandmark.LEFT_SHOULDER]
            punho_dir = lm[mp_pose.PoseLandmark.RIGHT_WRIST]
            punho_esq = lm[mp_pose.PoseLandmark.LEFT_WRIST]

            # Checar se ambos os punhos estão acima dos ombros
            if (punho_dir.y < ombro_dir.y) and (punho_esq.y < ombro_esq.y):
                frames_validos += 1
            else:
                frames_validos = 0

            # Visual
            cor = (0, 255, 0) if frames_validos > 0 else (0, 0, 255)
            h, w, _ = frame.shape
            for p in [punho_dir, punho_esq]:
                cx, cy = int(p.x * w), int(p.y * h)
                cv2.circle(frame, (cx, cy), 10, cor, -1)

            if frames_validos >= tolerancia_frames:
                print("✅ Dois braços levantados detectados!")
                return

        cv2.imshow("Aguardando dois braços levantados", frame)
        if cv2.waitKey(1) & 0xFF == 27:
            break


threading.Thread(target=interface, daemon=True).start()
t.sleep(2)

print("🎬 Iniciando leitura de gestos...")

detectar_levantar_braco()
t.sleep(TEMPO_ENTRE_GESTOS)

movimento_levantar_abaixar()
t.sleep(TEMPO_ENTRE_GESTOS)

esperar_dois_bracos_levantados()

print("✅ Dois Bracos Levantados detectados! Iniciando música final e encerrando sistema...")
tocar_video(2)

# Mantém o programa rodando até o vídeo terminar ou usuário pressionar 'q'
while True:
    if player is None:
        break
    if not player.is_playing():
        break
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    t.sleep(0.1)

cap.release()
cv2.destroyAllWindows()
