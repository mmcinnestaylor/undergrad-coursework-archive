.data

dialog	:.asciiz "

BEDFORD
Coward of France! how much he wrongs his fame,
Despairing of his own arm's fortitude,
To join with witches and the help of hell!

BURGUNDY
Traitors have never other company.
But what's that Pucelle whom they term so pure?

TALBOT
A maid, they say.

BEDFORD
A maid! and be so martial!

BURGUNDY
Pray God she prove not masculine ere long,
If underneath the standard of the French
She carry armour as she hath begun.

TALBOT
Well, let them practise and converse with spirits:
God is our fortress, in whose conquering name
Let us resolve to scale their flinty bulwarks.

BEDFORD
Ascend, brave Talbot; we will follow thee.

TALBOT
Not all together: better far, I guess,
That we do make our entrance several ways;
That, if it chance the one of us do fail,
The other yet may rise against their force.

BEDFORD
Agreed: I'll to yond corner.

BURGUNDY
And I to this.

TALBOT
And here will Talbot mount, or make his grave.
Now, Salisbury, for thee, and for the right
Of English Henry, shall this night appear
How much in duty I am bound to both.

Sentinels
Arm! arm! the enemy doth make assault!

ALENCON
How now, my lords! what, all unready so?

BASTARD OF ORLEANS
Unready! ay, and glad we 'scaped so well.

REIGNIER
'Twas time, I trow, to wake and leave our beds,
Hearing alarums at our chamber-doors.

ALENCON
Of all exploits since first I follow'd arms,
Ne'er heard I of a warlike enterprise
More venturous or desperate than this.

BASTARD OF ORLEANS
I think this Talbot be a fiend of hell.

REIGNIER
If not of hell, the heavens, sure, favour him.

ALENCON
Here cometh Charles: I marvel how he sped.

BASTARD OF ORLEANS
Tut, holy Joan was his defensive guard.

Enter CHARLES and JOAN LA PUCELLE

CHARLES
Is this thy cunning, thou deceitful dame?
Didst thou at first, to flatter us withal,
Make us partakers of a little gain,
That now our loss might be ten times so much?

JOAN LA PUCELLE
Wherefore is Charles impatient with his friend!
At all times will you have my power alike?
Sleeping or waking must I still prevail,
Or will you blame and lay the fault on me?
Improvident soldiers! had your watch been good,
This sudden mischief never could have fall'n.

CHARLES
Duke of Alencon, this was your default,
That, being captain of the watch to-night,
Did look no better to that weighty charge.

ALENCON
Had all your quarters been as safely kept
As that whereof I had the government,
We had not been thus shamefully surprised.

BASTARD OF ORLEANS
Mine was secure.

REIGNIER
And so was mine, my lord.

CHARLES
And, for myself, most part of all this night,
Within her quarter and mine own precinct
I was employ'd in passing to and fro,
About relieving of the sentinels:
Then how or which way should they first break in?

JOAN LA PUCELLE
Question, my lords, no further of the case,
How or which way: 'tis sure they found some place
But weakly guarded, where the breach was made.
And now there rests no other shift but this;
To gather our soldiers, scatter'd and dispersed,
And lay new platforms to endamage them.

Soldier
I'll be so bold to take what they have left.
The cry of Talbot serves me for a sword;
For I have loaden me with many spoils,
Using no other weapon but his name.

Exit

SCENE II. Orleans. Within the town.

Enter TALBOT, BEDFORD, BURGUNDY, a Captain, and others

BEDFORD
The day begins to break, and night is fled,
Whose pitchy mantle over-veil'd the earth.
Here sound retreat, and cease our hot pursuit.

Retreat sounded

TALBOT
Bring forth the body of old Salisbury,
And here advance it in the market-place,
The middle centre of this cursed town.
Now have I paid my vow unto his soul;
For every drop of blood was drawn from him,
There hath at least five Frenchmen died tonight.
And that hereafter ages may behold
What ruin happen'd in revenge of him,
Within their chiefest temple I'll erect
A tomb, wherein his corpse shall be interr'd:
Upon the which, that every one may read,
Shall be engraved the sack of Orleans,
The treacherous manner of his mournful death
And what a terror he had been to France.
But, lords, in all our bloody massacre,
I muse we met not with the Dauphin's grace,
His new-come champion, virtuous Joan of Arc,
Nor any of his false confederates.

BEDFORD
'Tis thought, Lord Talbot, when the fight began,
Roused on the sudden from their drowsy beds,
They did amongst the troops of armed men
Leap o'er the walls for refuge in the field.

BURGUNDY
Myself, as far as I could well discern
For smoke and dusky vapours of the night,
Am sure I scared the Dauphin and his trull,
When arm in arm they both came swiftly running,
Like to a pair of loving turtle-doves
That could not live asunder day or night.
After that things are set in order here,
We'll follow them with all the power we have.

Enter a Messenger

Messenger
All hail, my lords! which of this princely train
Call ye the warlike Talbot, for his acts
So much applauded through the realm of France?

TALBOT
Here is the Talbot: who would speak with him?

Messenger
The virtuous lady, Countess of Auvergne,
With modesty admiring thy renown,
By me entreats, great lord, thou wouldst vouchsafe
To visit her poor castle where she lies,
That she may boast she hath beheld the man
Whose glory fills the world with loud report.

BURGUNDY
Is it even so? Nay, then, I see our wars
Will turn unto a peaceful comic sport,
When ladies crave to be encounter'd with.
You may not, my lord, despise her gentle suit.

TALBOT
Ne'er trust me then; for when a world of men
Could not prevail with all their oratory,
Yet hath a woman's kindness over-ruled:
And therefore tell her I return great thanks,
And in submission will attend on her.
Will not your honours bear me company?

BEDFORD
No, truly; it is more than manners will:
And I have heard it said, unbidden guests
Are often welcomest when they are gone.

TALBOT
Well then, alone, since there's no remedy,
I mean to prove this lady's courtesy.
Come hither, captain.

\n\n"

returnres : .space 100
compareres: .space 100						#create temp save space for word comparisons


	.text
	.globl main

main:
	la $a0, dialog
	la $a1, returnres
	la $a2, compareres
	jal findmax

	li $v0,4			# now print the found longest word
	la $a0,returnres
	syscall

done:li $v0, 10		# Exit
	syscall

findmax:
          addi $sp, $sp, -4				#push stack down
          sw $ra, 0($sp)					#store return address in stack
					and $v1, $v1, $0				#set v1 to 0
L1:
          #and $v0, $v0, $0				#set v0 to 0
          jal getword							#call getword function
					bgt $v0, $v1, strcpy		#if returned word length is longer than saved
																	#word, then copy new word into compareres
strreturn:
          lb $t0, 0($a0)					#load character into t0
          bne $t0, 0, L1					#if t0 is not 0, loop again

					j finalcopy							#if entire string has been checked, copy
																	#longest word into returnres
finalreturn:
					lw $ra, 0($sp)					#load return address into ra
          addi $sp, $sp, 4				#push stack up
          jr $ra									#leave function

strcpy:														#copy new longest word in a1 to a2
					add $t1, $0, $a1
					add $t2, $0, $a2
strloop:  lb $t0, 0($t1)
					sb $t0, 0($t2)
					addi $t1, $t1, 1
					addi $t2, $t2, 1
				  bne $t0, 0, strloop
				  add $v1, $0, $v0
					j strreturn

finalcopy:												#copy longest word from a2 to a1
					add $t1, $0, $a1
					add $t2, $0, $a2
finloop:  lb $t0, 0($t2)
					sb $t0, 0($t1)
					addi $t1, $t1, 1
					addi $t2, $t2, 1
					bne $t0, 0, finloop
					add $v0, $0, $v1
					j finalreturn

getword:
					addi $sp, $sp, -4			#push stack down
					sw $ra, 0($sp)				#save ra onto stack
					jal isletter					#check whether or not first char is a letter
					beq $v0, 0, END				#if first char being checked not letter, exit
					and $v0, $v0, $0			#reinitialize v0 to 0
					add $t1, $0, $a1			#point t1 at the address of a1, the save space
L2:
          lb $t0, 0($a0)				#load next byte into t0
          addi $sp, $sp, -4			#push stack down
          sw $v0, 0($sp)				#store word length on stack
          jal isletter					#call isletter function
          beq $v0, 0, WORDend		#if v0 returns 0, jump to end of word code
          lw $v0, 0($sp)				#load word length into v0
          addi $sp, $sp, 4			#push stack up
          addi $v0, $v0, 1			#increment v0 by 1
          lb $t0, 0($a0),				#load byte into t0
          sb $t0, 0($t1)				#copy byte to save space
          addi $a0, $a0, 1			#increment a0 by one
          addi $t1, $t1, 1			#increment save space by 1
          j L2									#jump to top of loop
WORDend:
					lw $v0, 0($sp)				#load word length into v0
					addi $sp, $sp, 4			#push stack up
          sb $0, 0($t1)					#add a 0 onto end of word
END:
          lw $ra, 0($sp)				#load return address into ra
          addi $sp, $sp, 4			#push stack up
			    addi $a0, $a0, 1			#increment a0 by 1
          jr $ra								#return to findmax

isletter:
          lb  $t0, 0($a0)				#load char into t0
          blt $t0, 65, notchar	#if t0 is less than A, jump to not char
          blt $t0, 91, ischar		#if t0 is A-Z, jump to is char
          blt $t0, 97, notchar	#if t0 between Z and a, jump to not char
          blt $t0, 123, ischar	#if t0 is between z and a, jump to is char
          j notchar							#if t0 is greater than z, jump to not char
notchar:
          li $v0, 0							#set v0 to 0
          jr $ra								#return to get word
ischar:
          li $v0, 1							#set v0 to 1
          jr $ra								#return to get word
