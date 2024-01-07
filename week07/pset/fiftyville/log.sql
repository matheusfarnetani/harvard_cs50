-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2021
-- and that it took place on Humphrey Street.

-- Firs, get crime scene report
SELECT description
FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2021 AND street = 'Humphrey Street'

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present
-- at the time - each of their interview transcripts mentions the bakery.


-- The crime scene reports that there is three interviews for the crime
SELECT transcript
FROM interviews
WHERE day = 28 AND month = 7 AND year = 2021

-- First interview says that the thief got into a car in a
-- ten minutes time frame
SELECT *
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND hour = 10 AND minute < 30 AND activity = 'exit'

-- The second says that saw the thief withdrawing some money by the 
-- ATM on Legget Street
SELECT *
FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street'

-- The third says that saw the thief talking to somebody in a call for less than a minute
-- plannig to take the earlist flight out of fiftyville in the next day (29)
-- then the thief asked for the other person to buy the ticket

-- But in order to know wich call could be I need to know the people
-- that match in the first and second interview, to get their phone numbers
-- and see if there is someone in the list

SELECT *
FROM people
WHERE id IN
(
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
    (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28 AND month = 7 AND year = 2021
        AND atm_location = 'Leggett Street'
    )
)
AND license_plate IN 
(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28 AND month = 7 AND year = 2021
    AND hour = 10 AND minute < 30 AND activity = 'exit'
);

-- The results shows a couple of names:
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- Now to check the phonecalls
SELECT *
FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021
AND duration < 60 AND caller IN
(
    SELECT phone_number
    FROM people
    WHERE id IN
    (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN
        (
            SELECT account_number
            FROM atm_transactions
            WHERE day = 28 AND month = 7 AND year = 2021
            AND atm_location = 'Leggett Street'
        )
    )
    AND license_plate IN 
    (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE day = 28 AND month = 7 AND year = 2021
        AND hour = 10 AND minute < 30 AND activity = 'exit'
    )
);

-- The results are
-- 233|(367) 555-5533|(375) 555-8161|2021|7|28|45
-- 255|(770) 555-1861|(725) 555-3243|2021|7|28|49

-- Now I should get the owner's name of those phonenumbers and compare
-- with the airports, flights and passengers info.

-- Get caller's name
SELECT *
FROM people
WHERE phone_number IN
(
    SELECT caller
    FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021
    AND duration < 60 AND caller IN
    (
        SELECT phone_number
        FROM people
        WHERE id IN
        (
            SELECT person_id
            FROM bank_accounts
            WHERE account_number IN
            (
                SELECT account_number
                FROM atm_transactions
                WHERE day = 28 AND month = 7 AND year = 2021
                AND atm_location = 'Leggett Street'
            )
        )
        AND license_plate IN 
        (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE day = 28 AND month = 7 AND year = 2021
            AND hour = 10 AND minute < 30 AND activity = 'exit'
        )
    )
);

-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- Get receiver's name
SELECT *
FROM people
WHERE phone_number IN
(
    SELECT receiver
    FROM phone_calls
    WHERE day = 28 AND month = 7 AND year = 2021
    AND duration < 60 AND caller IN
    (
        SELECT phone_number
        FROM people
        WHERE id IN
        (
            SELECT person_id
            FROM bank_accounts
            WHERE account_number IN
            (
                SELECT account_number
                FROM atm_transactions
                WHERE day = 28 AND month = 7 AND year = 2021
                AND atm_location = 'Leggett Street'
            )
        )
        AND license_plate IN 
        (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE day = 28 AND month = 7 AND year = 2021
            AND hour = 10 AND minute < 30 AND activity = 'exit'
        )
    )
);

-- 847116|Philip|(725) 555-3243|3391710505|GW362R6
-- 864400|Robin|(375) 555-8161||4V16VO0

-- Now there is only two people that could be the thief
-- The first info I need from flights is to know the destination of
-- the first flight out of fiftyville the day after

SELECT city
FROM airports
WHERE id =
(
    SELECT destination_airport_id
    FROM flights
    WHERE day = 29 AND month = 7 AND year = 2021
    AND origin_airport_id =
    (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
    ORDER BY hour, minute
    LIMIT 1
);

-- The destination is New York City
-- Now I should check if Bruce or Diana was in the flight to New York

SELECT *
FROM people
WHERE passport_number IN
(
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 
    (
        SELECT id
        FROM flights
        WHERE day = 29 AND month = 7 AND year = 2021
        AND origin_airport_id =
        (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        ORDER BY hour, minute
        LIMIT 1
    )
);

-- Bruce was in the flight
-- Robin was the accomplice
-- New York was the destination