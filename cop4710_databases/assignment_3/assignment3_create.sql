CREATE TABLE MovieExec(
  name          CHAR(50),
  address       CHAR(75),
  certNum       INT,
  netWorth      INT,
  PRIMARY KEY   (certNum)
);
CREATE TABLE Studio(
  name          CHAR(50),
  address       CHAR(75),
  presCNum      INT,
  PRIMARY KEY   (name, address),
  FOREIGN KEY   (presCNum) REFERENCES MovieExec (certNum)
);
CREATE TABLE Movies(
  title         CHAR(50),
  year          INT,
  length        INT,
  genre         CHAR(20),
  studioName    CHAR(50),
  producerCNum  INT,
  PRIMARY KEY   (title, year),
  FOREIGN KEY   (studioName) REFERENCES Studio (name)
);
CREATE TABLE MovieStar(
  name          CHAR(50),
  address       CHAR(75),
  gender        CHAR(1),
  birthdate     DATE,
  PRIMARY KEY   (name, birthdate)
);
CREATE TABLE StarsIn(
  movieTitle    CHAR(50),
  movieYear     INT,
  starName      CHAR(50),
  PRIMARY KEY   (movieTitle, movieYear, starName),
  FOREIGN key   (movieTitle) REFERENCES Movies (title),
  FOREIGN KEY   (starName) REFERENCES MovieStar (name)
);
