CREATE DATABASE IF NOT EXISTS MauasaKataiRPG_DB;
USE MauasaKataiRPG_DB;

CREATE TABLE IF NOT EXISTS `player` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT UNIQUE,
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
    race INT,
    class INT
);

CREATE TABLE IF NOT EXISTS `auth` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    api_key VARCHAR(255) UNIQUE,
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
    item_id INT FOREIGN KEY REFERENCES item(id),
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
);

CREATE TABLE IF NOT EXISTS `throwable` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT FOREIGN KEY REFERENCES item(id),
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
    critical_damage DECIMAL(5, 2),1
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
);

CREATE TABLE IF NOT EXISTS `consumable` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT FOREIGN KEY REFERENCES item(id),
    effect VARCHAR(255),
    effect_duration INT,
    effect_chance DECIMAL(5, 2),
    effect_damage_min INT,
    effect_damage_max INT,
);

CREATE TABLE IF NOT EXISTS `armor` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT FOREIGN KEY REFERENCES item(id),
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
    extra_max_damage INT
);

CREATE TABLE IF NOT EXISTS `jewelry` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    item_id INT FOREIGN KEY REFERENCES item(id),
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
    extra_max_damage INT
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
    extra_luck INT,
);

CREATE TABLE IF NOT EXISTS `race` (
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

