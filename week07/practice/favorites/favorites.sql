sqlite3 favorites.db

.schema

SELECT * FROM shows;

SELECT * FROM shows
JOIN genres ON shows.id = genres.show_id:

UPDATE shows SET title = "How I Met Your Mother"
WHERE title = "How i met your mother";

UPDATE shows SET title = "Adventure Time"
WHERE title = "adventure time";

UPDATE shows SET title = "Arrow"
WHERE title = "arrow";

-- Avatar: The Last Airbender

UPDATE shows SET title = "Avatar: The Last Airbender"
WHERE title = "Avatar: the Last Airbender";

-- Brooklyn Nine-Nine

UPDATE shows SET title ="Brooklyn Nine-Nine"
WHERE title = "Brooklyn-99";

UPDATE shows SET title ="Brooklyn Nine-Nine"
WHERE title = "B99";

UPDATE shows SET title ="Brooklyn Nine-Nine"
WHERE title = "Brooklyn 99";

UPDATE shows SET title ="Brooklyn Nine-Nine"
WHERE title = "brooklyn 99";

-- Game of Thrones

UPDATE shows SET title ="Game of Thrones"
WHERE title = (
    SELECT * FROM shows
    WHERE title LIKE "%ones"
);

-- Grey’s Anatomy

UPDATE shows SET title ="Grey’s Anatomy"
WHERE title = (
    SELECT * FROM shows
    WHERE title LIKE "%ey%ato%";
);

-- It’s Always Sunny in Philadelphia

UPDATE shows SET title ="Grey’s Anatomy"
WHERE title = (
    SELECT * FROM shows
    WHERE title LIKE "%ways%";
);