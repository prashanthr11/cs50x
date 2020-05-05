select avg(rating)
from ratings
join
movies
where ratings.movie_id = movies.id and movies.year = 2012;