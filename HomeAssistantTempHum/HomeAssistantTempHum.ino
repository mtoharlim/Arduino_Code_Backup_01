#include <WiFi.h> // Perubahan utama: Menggunakan library WiFi untuk ESP32
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// --- KONFIGURASI PENGGUNA ---
// Ganti dengan kredensial WiFi Anda
const char* ssid = "Cloud#9-Lab";
const char* password = "l4bhcmlt9";

// Ganti dengan alamat IP atau nama host MQTT Broker (Home Assistant) Anda
const char* mqtt_server = "103.106.72.181";
const int mqtt_port = 1883;
// Jika Mosquitto broker Anda tidak memerlukan user & pass, biarkan kosong.
// Jika ya, isi sesuai dengan yang Anda buat di Home Assistant.
const char* mqtt_user = "MEDLOC"; // Contoh: "mqtt_user"
const char* mqtt_password = "MEDLOC"; // Contoh: "mqtt_password"

// Topik MQTT (ini akan digunakan di konfigurasi Home Assistant)
const char* temp_topic = "home/ruangtamu/temperature";
const char* humidity_topic = "home/ruangtamu/humidity";

// Konfigurasi Sensor DHT22
#define DHTPIN 15       // Pin tempat data DHT22 terhubung (misal: GPIO 15 di ESP32)
#define DHTTYPE DHT22   // Tipe sensor adalah DHT22
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi Klien
WiFiClient espClient;
PubSubClient client(espClient);

// Variabel untuk menyimpan nilai terakhir
float lastTemp = -999.0;
float lastHum = -999.0;

// Waktu tunda antar pengiriman data (dalam milidetik)
long lastMsg = 0;
const int interval = 3000; // Kirim data setiap 30 detik

// --- FUNGSI UTAMA ---

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  dht.begin();
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi terhubung");
  Serial.println("Alamat IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop sampai terhubung kembali
  while (!client.connected()) {
    Serial.print("Mencoba koneksi MQTT...");
    // Membuat client ID acak
    String clientId = "ESP32Client-"; // Diubah sedikit untuk identifikasi
    clientId += String(random(0xffff), HEX);
    
    // Mencoba terhubung
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("terhubung");
    } else {
      Serial.print("gagal, rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi dalam 5 detik");
      delay(1000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    // Membaca suhu dan kelembapan
    float h = dht.readHumidity();
    // Membaca suhu dalam Celsius
    float t = dht.readTemperature();

    // Cek jika pembacaan gagal
    if (isnan(h) || isnan(t)) {
      Serial.println("Gagal membaca dari sensor DHT!");
      return;
    }

    // Hanya kirim jika ada perubahan nilai
    if (t != lastTemp) {
      lastTemp = t;
      Serial.print("Mengirim Suhu: ");
      Serial.println(String(t).c_str());
      client.publish(temp_topic, String(t).c_str(), true);
    }

    if (h != lastHum) {
      lastHum = h;
      Serial.print("Mengirim Kelembapan: ");
      Serial.println(String(h).c_str());
      client.publish(humidity_topic, String(h).c_str(), true);
    }
  }
}
