# doesn't work due to flask need to use all processor

from multiprocessing import Process
import os
import time


# První skript: Flask aplikace
def run_flask_app():
    from flask import Flask, render_template
    from flask_sqlalchemy import SQLAlchemy

    # Získání absolutní cesty k databázi v kořenové složce projektu
    database_path = os.path.abspath('images_metadata.db')

    app = Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{database_path}'
    db = SQLAlchemy(app)

    # Model pro fotky
    class Photos(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        filename = db.Column(db.String(200), nullable=False)
        filepath = db.Column(db.String(500), nullable=False)
        position = db.Column(db.String(100), nullable=True)

    # Vytvoření tabulky, pokud ještě neexistuje - optional
    with app.app_context():
        db.create_all()

    @app.route('/')
    def index():
        photos = Photos.query.all()
        return render_template('index.html', photos=photos)

    app.run(debug=False)  # need to be False


# Druhý skript: Watchdog pro sledování nových obrázků
def run_watchdog():
    import sqlite3
    from watchdog.observers import Observer
    from watchdog.events import FileSystemEventHandler

    # Funkce pro přidání obrázku do databáze
    def add_photo_to_db(filename, filepath, position="N/A"):
        conn = sqlite3.connect('images_metadata.db', check_same_thread=False)
        cursor = conn.cursor()
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
            conn.close()

    # Handler pro sledování změn v adresáři
    class NewImageHandler(FileSystemEventHandler):
        def on_modified(self, event):
            if not event.is_directory and event.src_path.endswith(('.jpg', '.jpeg', '.png', '.JPG')):
                filename = os.path.basename(event.src_path)
                filepath = event.src_path
                add_photo_to_db(filename, filepath, "RA:14h Dec:+19°")

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


if __name__ == "__main__":
    # Vytvoření a spuštění obou procesů
    flask_process = Process(target=run_flask_app)
    watchdog_process = Process(target=run_watchdog)

    flask_process.start()
    watchdog_process.start()

    try:
        flask_process.join()
        watchdog_process.join()
    except KeyboardInterrupt:
        print("Ukončuji oba procesy...")
        flask_process.terminate()
        watchdog_process.terminate()