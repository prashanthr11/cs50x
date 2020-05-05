select DISTINCT(name) from people
join stars on people.id = stars.person_id
join movies ON stars.movie_id = movies.id
where movies.year = 2004
ORDER BY birth;