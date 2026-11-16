## Partie 1 ) 
Réponse question 1.2 :  Sans tail, le coût de l’ingestion croît, ce qui devient inutilisable sur de gros volumes. Avec tail, chaque ajout se fait en temps constant, donc le chargement complet coûte seulement n opérations (O(n)) : 150 pour 150 lignes, 10 millions pour 10 millions de lignes. 

Réponse question 2.4 : Oui. Après nettoyage, il reste 49 setosa, 48 versicolor et 46 virginica : les trois espèces sont présentes en quantités très proches.

Réponse question 3.5 : La fleur pas mélanger est la setosa d'après la matrice de confusion. Les 8 sont bien classé.
Les espèces qui se ressmeble sont les 2 autres versicolor et virginica.

En comparant les moyennes on constate que les valeurs sont très dispercés dispersées, ce qui suggère des groupes bien séparés. La setosa a de très petits pétales alors que les deux autres espèces ont des pétales plus grands et proches l’un de l’autre. C’est pour cela que la setosa est facile à reconnaître et que les deux autres se mélangent parfois


réponse question 3.6 : Avec k = 1, le modèle atteint 100 % sur le train car chaque fleur est son propre plus proche voisin : il mémorise les données. C'est du surapprentissage, d'où l'importance d'évaluer ses performances sur le jeu de test, composé de fleurs jamais vues.