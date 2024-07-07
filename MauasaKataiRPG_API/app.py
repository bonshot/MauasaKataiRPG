from flask import Flask, jsonify, request
from sqlalchemy.exc import SQLAlchemyError
from sqlalchemy import create_engine, text
from werkzeug.security import generate_password_hash

app = Flask(__name__)
from sqlalchemy import create_engine

DB_USER = 'root'
DB_PASSWORD = '1'
DB_HOST = 'mauasakatairpg_db'
DB_PORT = '3306'
DB_NAME = 'MauasaKataiRPG_DB'

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

@app.route('/')
def index():
    return 'Hello, World!'

@app.route('/api/users')
def users():
    query = 'SELECT * FROM users'
    return get_data(query)

@app.route('/api/add_user', methods=['POST'])
def add_user():
    try:
        data = request.get_json()
        username = data['username']
        password = generate_password_hash(data['password'])
        email = data['email']

        with engine.connect() as connection:
            query = '''
                INSERT INTO users (username, password, email, created_at) VALUES (:username, :password, :email, NOW())
            '''
            connection.execute(text(query), {'username': username, 'password': password, 'email': email})
            connection.commit()
            full_query = query.replace(':username', f"'{username}'").replace(':password', f"'{password}'").replace(':email', f"'{email}'")
            print(full_query)
        return jsonify({'message': 'User added successfully'})

    except SQLAlchemyError as e:
        print(e)
        return jsonify({'error': 'Failed to add user'}), 500



if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)