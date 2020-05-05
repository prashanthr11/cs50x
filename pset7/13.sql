select DISTINCT(PEOPLE.NAME) from people JOIN STARS ON STARS.PERSON_ID = PEOPLE.ID JOIN MOVIES
ON STARS.MOVIE_id IN (SELECT M.ID FROM movies as M
JOIN stars on M.id = stars.movie_id
JOIN people on stars.person_id = people.id
WHERE
name = "Kevin Bacon" and BIRTH = 1958)
WHERE NAME <> "Kevin Bacon";