from flask import Flask, render_template
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime
import os

# Získání absolutní cesty k databázi v kořenové složce projektu
database_path = os.path.abspath('images_metadata.db')
# print("Cesta k databázi:", database_path)

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{database_path}'
# app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)


# Model pro fotky
class Photos(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filename = db.Column(db.String(200), nullable=False)
    filepath = db.Column(db.String(500), nullable=False)
    position = db.Column(db.String(100), nullable=True)

    def __repr__(self):
        return f"<Photos {self.filename}>"


# Vytvoření tabulky, pokud ještě neexistuje
with app.app_context():
    db.create_all()  # Vytvoří tabulky na základě definovaných modelů


@app.route('/')
def index():
    # Načítání všech fotek z databáze
    photos = Photos.query.all()
    return render_template('index.html', photos=photos)


if __name__ == "__main__":
    app.run(debug=True)