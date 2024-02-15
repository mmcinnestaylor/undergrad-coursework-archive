CREATE TABLE Classes(
  classname     CHAR(50),
  type          CHAR(30),
  country       CHAR(30),
  numGuns       INT,
  bore          FLOAT,
  displacement  INT,
  PRIMARY KEY   (classname)
);
CREATE TABLE Ships(
  shipname      CHAR(50),
  classname     CHAR(50),
  launched      DATE,
  PRIMARY KEY   (shipname),
  FOREIGN KEY   (classname) REFERENCES Classes (classname)
);
CREATE TABLE Battles(
  battlename    CHAR(50),
  date          DATE,
  PRIMARY KEY   (battlename,date)
);
CREATE TABLE Outcomes(
  shipname      CHAR(50),
  battlename    CHAR(50),
  result        CHAR(7),
  PRIMARY KEY   (shipname, battlename),
  FOREIGN KEY   (shipname) REFERENCES Ships (shipname),
  FOREIGN KEY   (battlename) REFERENCES Battles (battlename)
);
