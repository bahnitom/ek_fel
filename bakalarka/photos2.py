import sqlite3
import os
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

# Funkce pro přidání obrázku do databáze
def add_photo_to_db(filename, filepath, position="N/A"):
    # Otevře nové připojení pro každý zápis do databáze
    conn = sqlite3.connect('images_metadata.db', check_same_thread=False)
    cursor = conn.cursor()

    # Vytvoření tabulky pro ukládání obrázků
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS photos (
            id INTEGER PRIMARY KEY,
            filename TEXT,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
            filepath TEXT,
            position TEXT
        )
    ''')
    conn.commit()

    try:
        cursor.execute("INSERT INTO photos (filename, filepath, position) VALUES (?, ?, ?)",
                       (filename, filepath, position))
        conn.commit()
        print(f"Nový obrázek '{filename}' přidán do databáze.")
    except sqlite3.IntegrityError:
        print(f"Obrázek '{filename}' už v databázi existuje.")
    finally:
        conn.close()  # Zavře připojení po každém zápisu


# Handler pro sledování změn v adresáři
class NewImageHandler(FileSystemEventHandler):
    def on_created(self, event):
        if not event.is_directory and event.src_path.endswith(('.jpg', '.jpeg', '.png')):
            filename = os.path.basename(event.src_path)
            filepath = event.src_path
            add_photo_to_db(filename, filepath, "RA:14h Dec:+19°")  # Příklad pozice


# Nastavení sledování adresáře
watch_directory = '/Users/tomasbahnik/Pictures'
event_handler = NewImageHandler()
observer = Observer()
observer.schedule(event_handler, path=watch_directory, recursive=False)
observer.start()

try:
    print(f"Sledování nových obrázků v '{watch_directory}'... (CTRL+C pro ukončení)")
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print("Ukončuji sledování...")
    observer.stop()

observer.join()
