from flask import Flask, jsonify, request
from sqlalchemy.exc import SQLAlchemyError
from sqlalchemy import create_engine, text
from werkzeug.security import generate_password_hash
import os, requests
from dotenv import load_dotenv

app = Flask(__name__)

load_dotenv()
DB_USER = os.getenv('DB_USER')
DB_PASSWORD = os.getenv('DB_PASSWORD')
DB_HOST = os.getenv('DB_HOST')
DB_PORT = os.getenv('DB_PORT')
DB_NAME = os.getenv('DB_NAME')

db_url = f"mysql+mysqlconnector://{DB_USER}:{DB_PASSWORD}@{DB_HOST}:{DB_PORT}/{DB_NAME}"
engine = create_engine(db_url)

def get_data(query):
    try:
        with engine.connect() as connection:
            result = connection.execute(text(query))
            data = []
            columns = result.keys()
            for row in result:
                data_dict = dict(zip(columns, row))
                data.append(data_dict)

        return jsonify(data[0]) if len(data) == 1 else jsonify(data)

    except SQLAlchemyError as e:
        return jsonify({'error': str(e.__dict__['orig'])})

def get_extrapolated_data(query, field):
    print(query)
    print(field)


@app.route('/api/users', strict_slashes=False)
def users():
    query = 'SELECT * FROM player'
    return get_data(query)

@app.route('/api/add_user', methods=['POST'], strict_slashes=False)
def add_user():
    try:
        data = request.get_json()
        username = data['username']
        password = generate_password_hash(data['password'])
        email = data['email']

        with engine.begin() as connection:  # Use begin() for transaction
            query = '''
                INSERT INTO users (username, password, email, created_at) VALUES (:username, :password, :email, NOW())
            '''
            connection.execute(text(query), {'username': username, 'password': password, 'email': email})

        return jsonify({'message': 'User added successfully'})

    except SQLAlchemyError as e:
        return jsonify({'error': 'Failed to add user', 'data': data}), 500

@app.route('/api/classes', methods=['GET'], strict_slashes=False)
def get_classes():
    query = f'SELECT * FROM classes'
    return get_data(query)

@app.route('/api/classes/<string:data>', methods=['GET'], strict_slashes=False)
def get_class(data):
    query = f'SELECT * FROM classes WHERE name = "{data}"'
    return get_data(query)

@app.route('/api/races', methods=['GET'], strict_slashes=False)
def get_races():
    query = f'SELECT * FROM races'
    data = get_data(query)
    return data

@app.route('/api/races/<string:data>', methods=['GET'], strict_slashes=False)
def get_race(data):
    if(data == 'Dark_elf'):
       data = 'Dark elf'
    query = f'SELECT * FROM races WHERE name = "{data}"'
    return get_data(query)

def process_attributes(user_race, user_class):
    url_class = f'http://127.0.0.1:5000/api/classes/{user_class}'
    url_race = f'http://127.0.0.1:5000/api/races/{user_race}'
    class_data = requests.get(url_class).json()
    race_data = requests.get(url_race).json()
    attributes = {
        'vigor': class_data['extra_vigor'],
        'strength': class_data['extra_strength'],
        'dexterity': class_data['extra_dexterity'],
        'concentration': class_data['extra_concentration'],
        'intelligence': class_data['extra_intelligence'],
        'faith': class_data['extra_faith'],
        'luck': class_data['extra_luck'],

        'extra_health': race_data['extra_health'],
        'extra_mana': race_data['extra_mana'],
        'extra_conviction': race_data['extra_conviction'],
        'extra_stamina': race_data['extra_stamina'],
        'extra_armor': race_data['extra_armor'],
        'extra_magic_resistance': race_data['extra_magic_resistance']
    }

    print(attributes)

    return attributes

def insert_data(user_data, attributes):
    try:
        with engine.begin() as connection:
            query = '''
                INSERT INTO player (user_id, user_name, level, experience, vigor, strength, dexterity, intelligence, faith, luck, base_health, base_mana, base_conviction, base_armor, base_magic_resistance, location, class)
                VALUES(:user_id, :user_name, :level, :experience, :vigor, :strength, :dexterity, :intelligence, :faith, :luck, :extra_health, :extra_mana, :extra_conviction, :extra_armor, :extra_magic_resistance, :location, :class)'''

            connection.execute(text(query), {
                'user_id': user_data['user_id'],
                'user_name': user_data['user_name'],
                'level': user_data['level'],
                'experience': user_data['experience'],
                'vigor': attributes['vigor'],
                'strength': attributes['strength'],
                'dexterity': attributes['dexterity'],
                'intelligence': attributes['intelligence'],
                'faith': attributes['faith'],
                'luck': attributes['luck'],
                'extra_health': attributes['extra_health'],
                'extra_mana': attributes['extra_mana'],
                'extra_conviction': attributes['extra_conviction'],
                'extra_armor': attributes['extra_armor'],
                'extra_magic_resistance': attributes['extra_magic_resistance'],
                'location': user_data['location'],
                'class': user_data['class']
            })
            
        return jsonify({'message': 'User registered successfully'})
    except SQLAlchemyError as e:
        return jsonify({'error': str(e.__dict__['orig'])}), 500

@app.route('/api/register', methods=['POST'], strict_slashes=False)
def register():
    try:
        data = request.get_json()
        user_id = data['user_id']
        user_name = data['user_name']
        user_race = data['race']
        user_class = data['class']
        attributes = process_attributes(user_race, user_class)
        user_data = {
            'user_id': user_id,
            'user_name': user_name,
            'level': 1,
            'experience': 0,
            'location': 1,
            'race': user_race,
            'class': user_class
        }
        return insert_data(user_data, attributes)

    except Exception as e:
        return jsonify({'error': str(e)}), 500

@app.route('/')
def index():
    return 'Hello, World!'

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)