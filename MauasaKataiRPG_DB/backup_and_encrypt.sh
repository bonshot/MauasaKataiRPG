echo "STARTING BACKUP AT $(date +%Y%m%d%H%M%S)"

mysqldump -u root -p1 MauasaKataiRPG_DB > Backup/backup_latest.sql

if [ -f Backup/backup_latest.enc ]; then
    echo "BACKUP DETECTED, DELETING..."
    rm Backup/backup_latest.enc
    echo "BACKUP DELETE DONE"
fi

if [ ! -f Key/database_public_key.pem ]; then
    echo "Public Key not found, creating..."
    openssl genrsa -out Key/database_private_key.pem 2048
    openssl rsa -pubout -in Key/database_private_key.pem -out Key/database_public_key.pem
    echo "Public Key created at Key/database_public_key.pem"
    cat Key/database_public_key.pem
fi

openssl rand -base64 32 > symmetric_key.bin
openssl enc -aes-256-cbc -salt -in Backup/backup_latest.sql -out Backup/backup_latest.enc -pass file:symmetric_key.bin
openssl rsautl -encrypt -inkey Key/database_public_key.pem -pubin -in symmetric_key.bin -out Key/symmetric_key.enc

rm symmetric_key.bin Backup/backup_latest.sql

echo "BACKUP DONE"
