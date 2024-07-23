if [ -f .env ]; then
    export $(cat .env | xargs)
fi

if [ -f "./Backup/backup_latest.enc" ]; then
    echo "\n\n\n\n\e[32mEncrypted backup detected, starting decryption process...\e[0m"
    
    openssl pkeyutl -decrypt -inkey ./Key/database_private_key.pem -in ./Key/symmetric_key.enc -out symmetric_key.bin
    if [ $? -ne 0 ]; then
        echo "\e[31mError decrypting symmetric key\e[0m"
        exit 1
    fi

    openssl enc -d -aes-256-cbc -pbkdf2 -iter ${ITER} -in ./Backup/backup_latest.enc -out ./Backup/backup_latest_decrypted.sql -pass file:symmetric_key.bin
    if [ $? -ne 0 ]; then
        echo "\e[31mError decrypting SQL backup file\e[0m"
        exit 1
    fi

    mv ./Backup/backup_latest_decrypted.sql ../docker-entrypoint-initdb.d/setup.sql
    echo "\e[32mDecryption and database restore completed successfully.\e[0m\n\n\n\n"
else
    echo "\e[31mNo encrypted backup found.\e[0m\n\n\n\n"
fi