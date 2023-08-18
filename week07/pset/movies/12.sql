-- In 12.sql, write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
--     Your query should output a table with a single column for the title of each movie.
--     You may assume that there is only one person in the database with the name Bradley Cooper.
--     You may assume that there is only one person in the database with the name Jennifer Lawrence.

SELECT title
FROM movies

-- First join stars on movies
JOIN stars stars1 ON movies.id = stars1.movie_id

-- Then join people into stars
JOIN people p1 ON stars1.person_id = p1.id

-- Do the same process again, in order to be able to search two values
-- in the same table at the same time
JOIN stars stars2 ON movies.id = stars2.movie_id
JOIN people p2 ON stars2.person_id = p2.id

-- Search through that enormous table
WHERE p1.name = 'Bradley Cooper' AND p2.name = 'Jennifer Lawrence';
