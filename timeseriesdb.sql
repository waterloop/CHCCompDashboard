CREATE DATABASE timeseries_db;
\c timeseries_db
CREATE EXTENSION IF NOT EXISTS timescaledb;


CREATE TABLE telemetry_fields
(
	field_id serial NOT NULL,
	field varchar(255) NOT NULL,
	PRIMARY KEY (field_id)
);

CREATE TABLE telemetry
(
	field_id int NOT NULL,
	telemetry_data float NOT NULL,
	datetime timestamp NOT NULL,
	FOREIGN KEY (field_id) REFERENCES telemetry_fields(field_id)
);

--converts telemetry into a time series table
SELECT create_hypertable('telemetry', 'datetime');
	
INSERT INTO telemetry_fields 
	(field) 
VALUES
	('BATTERY_PACK_CURRENT'),
	('AVERAGE_CELL_TEMPERATURE'),
	('IGBT_TEMPERATURE'),
	('MOTOR_VOLTAGE'),
	('BATTERY_PACK_VOLTAGE'),
	('BUCK_TEMPERATURE'),
	('BMS_CURRENT'),
	('LINK_CAP_VOLTAGE'),
	('MOTOR_CURRENT'),
	('BATTERY_CURRENT'),
	('BATTERY_VOLTAGE'),
	('SPEED'),
	('TORCHIC_1'),
	('TORCHIC_2'),
	('PRESSURE_HIGH'),
	('PRESSURE_LOW_1'),
	('PRESSURE_LOW_2');

\q