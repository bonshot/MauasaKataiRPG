FROM mysql:8.0-debian
RUN apt-get update && apt-get install -y cron screen systemd nano

WORKDIR /MauasaKataiRPG_DB
COPY ./MauasaKataiRPG_DB .

RUN chmod +x decrypt_and_restore.sh
RUN sh decrypt_and_restore.sh

RUN echo "0 */2 * * * /MauasaKataiRPG_DB/backup_and_encrypt.sh" > /etc/cron.d/backup_cron
RUN echo "*/5 * * * * rm -f /docker-entrypoint-initdb.d/setup.sql" >> /etc/cron.d/backup_cron
RUN chmod 0644 /etc/cron.d/backup_cron
RUN crontab /etc/cron.d/backup_cron
RUN touch /var/log/cron.log

EXPOSE 3306
CMD ["bash", "-c", "cron && docker-entrypoint.sh mysqld"]