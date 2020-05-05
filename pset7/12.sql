SELECT TITLE FROM movies 
JOIN stars on  movies.id = stars.movie_id 
JOIN people on stars.person_id = people.id 
WHERE 
name = "Johnny Depp" 
intersect 
SELECT TITLE FROM movies 
JOIN stars on movies.id = stars.movie_id 
JOIN people on stars.person_id = people.id 
WHERE 
name = "Helena Bonham Carter"
