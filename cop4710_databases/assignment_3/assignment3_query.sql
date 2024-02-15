SELECT name
FROM MovieStar
WHERE gender = 'M'
AND name IN (SELECT starName FROM StarsIn
             WHERE movieTitle = 'Titanic');

SELECT starName
FROM StarsIn
WHERE movieTitle IN (SELECT title FROM Movies
                    WHERE studioName = 'MGM' AND year = 1995);

SELECT name
FROM MovieExec
WHERE certNum IN (SELECT presCNum FROM Studio
                  WHERE name = 'MGM');
