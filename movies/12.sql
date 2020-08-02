SELECT movies.title FROM movies
WHERE movies.id IN (SELECT stars.movie_id as test1 FROM stars
WHERE EXISTS (SELECT stars.movie_id as test2 FROM stars
WHERE stars.person_id = (SELECT people.id FROM people
JOIN stars ON stars.person_id = people.id
WHERE people.name = 'Helena Bonham Carter'
AND test1 = test2))
AND stars.person_id = (SELECT people.id FROM people
JOIN stars ON stars.person_id = people.id
WHERE people.name = 'Johnny Depp'))