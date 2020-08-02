SELECT DISTINCT people.name FROM people
WHERE people.id IN (SELECT stars.person_id FROM stars
WHERE stars.movie_id IN (SELECT stars.movie_id FROM stars
WHERE stars.person_id = (SELECT stars.person_id FROM stars
JOIN people ON people.id = stars.person_id
WHERE people.name = 'Kevin Bacon' AND people.birth = '1958')))
AND NOT people.name = 'Kevin Bacon'