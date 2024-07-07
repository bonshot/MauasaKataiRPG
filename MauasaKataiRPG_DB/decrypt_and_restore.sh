if [ -f "/MauasaKataiRPG_DB/Backup/backup_latest.enc" ]; then
    echo "Encrypted backup detected, starting decryption process..."
    openssl rsautl -decrypt -inkey Key/database_private_key.pem -in Key/symmetric_key.enc -out symmetric_key.bin
    if [ $? -ne 0 ]; then
        echo "Error decrypting symmetric key"
        exit 1
    fi

    openssl enc -d -aes-256-cbc -in /MauasaKataiRPG_DB/Backup/backup_latest.enc -out /MauasaKataiRPG_DB/Backup/backup_latest_decrypted.sql -pass file:symmetric_key.bin
    if [ $? -ne 0 ]; then
        echo "Error decrypting SQL backup file"
        exit 1
    fi

    cp /MauasaKataiRPG_DB/Backup/backup_latest_decrypted.sql /docker-entrypoint-initdb.d/setup.sql
    
    echo "Decryption and database restore completed successfully."
else
    echo "No encrypted backup found."
fi
