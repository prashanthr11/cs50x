SELECT TITLE FROM MOVIES
JOIN RATINGS ON MOVIES.ID = RATINGS.MOVIE_ID
JOIN STARS ON RATINGS.MOVIE_ID = STARS.MOVIE_ID 
JOIN PEOPLE ON PEOPLE.ID = STARS.PERSON_ID
WHERE 
PEOPLE.NAME = "Chadwick Boseman"
ORDER BY RATING DESC
LIMIT 5;