CREATE DATABASE IF NOT EXISTS MauasaKataiRPG_DB;
USE MauasaKataiRPG_DB;

CREATE TABLE IF NOT EXISTS `player` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id BIGINT UNIQUE,
    user_name VARCHAR(255) UNIQUE,
    level INT,
    experience INT,
    vigor INT,
    strength INT,
    dexterity INT,
    concentration INT,
    intelligence INT,
    faith INT,
    luck INT,
    base_health INT,
    base_mana INT,
    base_conviction INT,
    base_stamina INT,
    base_armor INT,
    base_magic_resistance INT,
    location INT,
    race VARCHAR(50),
    class VARCHAR(50)
);

CREATE TABLE IF NOT EXISTS `auth` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    api_key VARCHAR(255) UNIQUE
);

CREATE TABLE IF NOT EXISTS `item` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    type VARCHAR(255),
    rarity VARCHAR(255),
    price INT,
    description VARCHAR(255),
    max_stack INT
);

CREATE TABLE IF NOT EXISTS `weapon` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT,
    min_dmg INT,
    max_dmg INT,
    level_required INT,
    scale_str DECIMAL(5, 2),
    scale_dex DECIMAL(5, 2),
    scale_int DECIMAL(5, 2),
    scale_fth DECIMAL(5, 2),
    scale_arm DECIMAL(5, 2),
    scale_hp DECIMAL(5, 2),
    scale_luck DECIMAL(5, 2),
    critical_chance DECIMAL(5, 2),
    critical_damage DECIMAL(5, 2),
    damage_type VARCHAR(255),
    venom_chance DECIMAL(5, 2),
    venom_duration INT,
    freeze_chance DECIMAL(5, 2),
    freeze_duration INT,
    paralysis_chance DECIMAL(5, 2),
    paralysis_duration INT,
    effect_damage_min INT,
    effect_damage_max INT,
    effect_chance DECIMAL(5, 2),
    FOREIGN KEY (item_id) REFERENCES item(id)
);

CREATE TABLE IF NOT EXISTS `throwable` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT,
    min_dmg INT,
    max_dmg INT,
    level_required INT,
    scale_str DECIMAL(5, 2),
    scale_dex DECIMAL(5, 2),
    scale_int DECIMAL(5, 2),
    scale_fth DECIMAL(5, 2),
    scale_arm DECIMAL(5, 2),
    scale_luck DECIMAL(5, 2),
    critical_chance DECIMAL(5, 2),
    critical_damage DECIMAL(5, 2),
    damage_type VARCHAR(255),
    venom_chance DECIMAL(5, 2),
    venom_duration INT,
    freeze_chance DECIMAL(5, 2),
    freeze_duration INT,
    paralysis_chance DECIMAL(5, 2),
    paralysis_duration INT,
    effect_damage_min INT,
    effect_damage_max INT,
    effect_chance DECIMAL(5, 2),
    FOREIGN KEY (item_id) REFERENCES item(id)
);

CREATE TABLE IF NOT EXISTS `consumable` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT,
    effect VARCHAR(255),
    effect_duration INT,
    effect_chance DECIMAL(5, 2),
    effect_damage_min INT,
    effect_damage_max INT,
    FOREIGN KEY (item_id) REFERENCES item(id)
);

CREATE TABLE IF NOT EXISTS `armor` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT,
    armor INT,
    magic_resistance INT,
    level_required INT,
    scale_str DECIMAL(5, 2),
    scale_dex DECIMAL(5, 2),
    scale_int DECIMAL(5, 2),
    scale_fth DECIMAL(5, 2),
    scale_arm DECIMAL(5, 2),
    scale_hp DECIMAL(5, 2),
    extra_health INT,
    extra_mana INT,
    extra_faith INT,
    extra_luck INT,
    extra_stamina INT,
    extra_min_damage INT,
    extra_max_damage INT,
    FOREIGN KEY (item_id) REFERENCES item(id)
);

CREATE TABLE IF NOT EXISTS `jewelry` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT,
    level_required INT,
    scale_str DECIMAL(5, 2),
    scale_dex DECIMAL(5, 2),
    scale_int DECIMAL(5, 2),
    scale_fth DECIMAL(5, 2),
    scale_arm DECIMAL(5, 2),
    scale_hp DECIMAL(5, 2),
    extra_health INT,
    extra_mana INT,
    extra_faith INT,
    extra_luck INT,
    extra_stamina INT,
    extra_min_damage INT,
    extra_max_damage INT,
    FOREIGN KEY (item_id) REFERENCES item(id)
);

CREATE TABLE IF NOT EXISTS `classes` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    description VARCHAR(255),
    extra_vigor INT,
    extra_strength INT,
    extra_dexterity INT,
    extra_intelligence INT,
    extra_faith INT,
    extra_luck INT
);

CREATE TABLE IF NOT EXISTS `races` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255),
    description VARCHAR(255),
    extra_health INT,
    extra_mana INT,
    extra_conviction INT,
    extra_stamina INT,
    extra_armor INT,
    extra_magic_resistance INT
);

/* INSERT INTO `auth` VALUES (1,'07766140ba3fb073657b7ef06a16947521301bb68f912f1a6d041bbd6358e198','api_key_bot'); */

INSERT INTO `classes`(name, description, extra_vigor, extra_strength, extra_dexterity, extra_intelligence, extra_faith, extra_luck) VALUES
('Warrior', 'A strong, sturdy and reckless fighter that only cares about battle.', 5, 5, 2, 1, 1, 1),
('Rogue', 'A sneaky and agile assassin that strikes when no one is watching.', 2, 2, 5, 1, 1, 5),
('Mage', 'A scholar of stars and elements devoted by the knowledge acquired by the years.', 1, 1, 1, 5, 5, 2),
('Cleric', 'An agile fighter well known for its versatility and a bit of knowledge of everything.', 2, 2, 1, 1, 5, 5),
('Paladin', 'A warrior with fortitude devoted by its faith.', 5, 5, 1, 2, 2, 2),
('Bard', 'An agile fighter, with a little knowledge of supportive magic, and an excelent musician.', 2, 1, 5, 2, 2, 5),
('Priest', 'A fully devote by its faith, it depends of its conviction.', 2, 2, 2, 2, 2, 5),
('Warlock', 'A scholar of dark arts, reckless with the use of the health points.', 1, 1, 1, 5, 5, 2),
('Ranger', 'A scholar of nature and an agile fighter.', 2, 2, 2, 5, 2, 2);

INSERT INTO `races`(name, description, extra_health, extra_mana, extra_conviction, extra_stamina, extra_armor, extra_magic_resistance) VALUES
('Human', 'Versatile but fragile, with a balanced conviction and strength', 20, 20, 40, 30, 5, 5),
('Elf', 'Agile and wise, their long lifespan makes possible to master the arts of magic, but fragile.', 10, 50, 10, 30, 5, 20),
('Dark elf', 'They are close to their brothers the elves, but the circumstances made them change their ways. they practice the dark arts and they are stronger', 30, 0, 0, 30, 20, 0),
('Dwarf', 'Strong and reckless, not very smart, but they are strong together', 50, 0, 0, 10, 20, 0),
('Orc', 'Strong and brave fighters, they are common for their use of the dark arts.', 35, 10, 10, 20, 20, 10),
('Giant', 'Extremely strong, they are very sturdy, but not very smart.', 100, 0, 0, 10, 20, 0),
('Goblin', 'Small and agile, they are good for being sneaky.', 0, 0, 0, 60, 0, 10),
('Undead', 'Fragile but very smart users of the dark arts, they are not very strong', 0, 20, 0, 10, 0, 20),
('Gnome', 'Close to their dwarf brothers, but they chose the path of knowledge instead of the strength', 20, 60, 0, 10, 5, 15);