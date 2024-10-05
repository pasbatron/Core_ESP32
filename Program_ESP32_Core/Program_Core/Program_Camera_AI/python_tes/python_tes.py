import serial
import time

SERIAL_PORT = 'COM5'
BAUD_RATE = 115200

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

def read_from_serial():
    while ser.in_waiting > 0:
        data = ser.readline().decode('utf-8').strip()
        print(f"Received data: {data}")

def send_to_serial(data):
    ser.write(data.encode('utf-8') + b'\n')

try:
    print("Koneksi serial berhasil.")
    
    # Inisialisasi dengan input pertama
    trigger_message = input("Masukkan perintah untuk memulai pengiriman data (atau ketik 'exit' untuk keluar): ")
    
    while trigger_message.lower() != 'exit':
        # Kirim data berdasarkan trigger yang diberikan
        send_to_serial(trigger_message)
        read_from_serial()
        
        while True:
            # Tunggu input baru
            new_trigger_message = input("Masukkan perintah baru untuk mengupdate pengiriman data (atau ketik 'exit' untuk keluar): ")
            
            if new_trigger_message.lower() == 'exit':
                raise KeyboardInterrupt  # Menghentikan program
            
            if new_trigger_message != trigger_message:
                # Update trigger dan kirim data baru
                trigger_message = new_trigger_message
                send_to_serial(trigger_message)
                read_from_serial()
            else:
                print(f"Tunggu input baru atau ketik 'exit' untuk keluar.")
            
            time.sleep(1)  # Tunggu sebelum memeriksa input lagi

except KeyboardInterrupt:
    print("Program dihentikan oleh pengguna.")

finally:
    ser.close()
    print("Koneksi serial ditutup.")
