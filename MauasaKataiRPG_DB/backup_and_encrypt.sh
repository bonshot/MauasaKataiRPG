echo "STARTING BACKUP AT $(date +%Y/%m/%d %H:%M:%S)"

if [ -f .env ]; then
    export $(cat .env | xargs)
fi

mysqldump -u root -p"${MYSQL_ROOT_PASSWORD}" "${MYSQL_DATABASE}" > ./Backup/backup_latest.sql

if [ -f Backup/backup_latest.enc ]; then
    echo "BACKUP DETECTED, DELETING..."
    rm ./Backup/backup_latest.enc
    echo "BACKUP DELETE DONE"
fi

if [ ! -f ./Key/database_public_key.pem ]; then
    echo "Public Key not found, creating..."
    openssl genrsa -out ./Key/database_private_key.pem 2048
    openssl rsa -pubout -in ./Key/database_private_key.pem -out ./Key/database_public_key.pem
    echo "Public Key created at Key/database_public_key.pem"
    cat ./Key/database_public_key.pem
fi

openssl rand -base64 32 > symmetric_key.bin
openssl enc -aes-256-cbc -pbkdf2 -iter ${ITER} -salt -in ./Backup/backup_latest.sql -out ./Backup/backup_latest.enc -pass file:symmetric_key.bin
openssl pkeyutl -encrypt -inkey ./Key/database_public_key.pem -pubin -in symmetric_key.bin -out ./Key/symmetric_key.enc
cp ./Backup/backup_latest.enc ./Backup/backup_$(date +%Y_%m_%d_%H_%M_%S).enc

rm symmetric_key.bin ./Backup/backup_latest.sql

echo "BACKUP DONE"
