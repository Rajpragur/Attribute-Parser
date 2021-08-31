# Attribute-Parser
Hackerrank challenge
Challenge link :- https://www.hackerrank.com/challenges/attribute-parser/problem

You have to take input of first Two Int - N ~ number of lines , Q ~ number of queries
then you will be provided input like this:-
4 3 | This is the number of lines and Number of queries

These are lines
Half of them are closing attributes on which we don't have to do too much
<tag1 value = "HelloWorld"> 
<tag2 name = "Name1">
</tag2>
</tag1>

This is the queries
The query after the last dot(If there) is the main query before that everything should be ignored

tag1.tag2~name | In this tag2-name is the query  | Tag1 should be ignored
tag1~name
tag1~value
