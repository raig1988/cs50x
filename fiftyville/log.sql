-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2021 AND street = 'Humphrey Street';
-- Allows me to read the description of the crime report and show me the next step

SELECT id, name, transcript FROM interviews WHERE month = 7 AND day = 28 AND year = 2021;
-- Query to read interviews of witnesses hoping to get the next step for the case.
-- Ruth :within 10 min of the theft, thief got into a car in bakery parking lot and drive away. Security footage, look for cars
-- Eugene: someone he recognizes, earlier this morning 7/28/2021, by the ATM on Leggett Street the thief was withdrawing money
-- Raymond: as thief leaving the bakery, called someone for less than a min. Thief planning to take earliest flight out of 50ville on 7/29/2021. Other person purchase the ticket.

SELECT id, activity, license_plate, minute FROM bakery_security_logs WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute < 25 AND activity = 'exit';
-- Query to get license plates from suspects leaving within 10 minutes of the theft

SELECT id, account_number, transaction_type, amount FROM atm_transactions WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' ORDER BY amount DESC;
-- Query to get info from withdrawals according to witness accounts ordering transactions from more to less amount.
-- Found coincidences in ID for 264 = 20, 266 = 60 and 267 = 50 with license plates from sec footage.

SELECT id, caller, receiver, duration FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60;
-- Query to get the lists of phone numbers from callers and receivers with less than a minute to get more info from the possible suspect.

SELECT id, abbreviation, full_name FROM airports WHERE city = "Fiftyville";
-- Query to get the id, abbreviation and full name of Fiftyville airport in order to query flights.
-- Origin airport id = 8 and abbrev CSF

SELECT id, destination_airport_id, hour, minute FROM flights WHERE month = 7 AND day = 29 AND year = 2021 AND origin_airport_id = 8;
-- Query to find the earliest flight which is at 8:20 am with id = 36 and destination_airport_id = 4

SELECT passport_number, seat FROM passengers WHERE flight_id = 36;
-- Query to find the list of passengers from the earliest flight leaving Fiftyville 29th morning

SELECT person_id, creation_year FROM bank_accounts WHERE account_number = 28296815 OR account_number = 76054385 OR account_number = 49610011;
-- Query to find the list of people id that withdrew money from the ATM according with license plate matchings
-- 3 suspects 686048, 395717, 449774

SELECT id, name, phone_number, passport_number, license_plate FROM people WHERE id = 686048 OR id = 395717 OR id = 449774;
-- Query to obtain info about the 3 suspects. Kenny is in flight (seat 7a), Taylor in flight (seat 6d), Bruce in flight (seat 4a). All 3 called.
-- Kenny called to number (066) 555-9701, Taylor called to number (676) 555-6554, Bruce called to (375) 555-8161.
-- Only Bruce license plate appears at the exit footage with id = 261, 94kL13X
-- Bruce acommplice could be (375) 555-8161.

SELECT id, name FROM people WHERE phone_number = '(375) 555-8161';
-- Query to obtain accomplice info. Could be Robin.

SELECT full_name, city FROM airports WHERE id = 4;
-- Query to obtain the destination airport id. La Guardia Airport in New York City.



