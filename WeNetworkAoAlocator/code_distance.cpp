/*Fait par Youen MAUFROY*/
#include "code_distance.h"
#include "QDebug"


Code_distance::Code_distance(){}
Code_distance::~Code_distance(){}

// Convertit les angles en radiants
double Code_distance::radians(double degree)
{
    double pi = 3.14159265358979323846;
    return (degree * (pi / 180));
}

/* Fonction permettant de retrouver les coordonnées d'une intersection des données de deux locators.
Prend en entrée la position de deux locators et leur angle trouvé
Sort un vecteur avec les coordonnées (x, y) de l'intersection */
vector<double> Code_distance::intersection(double x_1, double y_1, double angle_1, double x_2, double y_2, double angle_2) {
    // Si deux angles sont égaux, les droites sont parallèles, on enlève 0.1 degré pour éviter ça
    if (angle_1 == angle_2) {
        angle_1 -= 0.1;
    }
    /* Formule pour obtenir les coordonnées de l'intersection de deux droites
    sachant qu'une droite est générée à partir d'un point et d'un angle */
    double xf = (y_2 - y_1 + tan(radians(angle_1)) * x_1 - tan(radians(angle_2)) * x_2) /
        (tan(radians(angle_1)) - tan(radians(angle_2)));
    double yf = tan(radians(angle_1)) * (xf - x_1) + y_1;
    double verif = quarter_verif({xf, yf, x_1, y_1,angle_1, x_2, y_2,angle_2 });
    std::vector<double> position = { xf, yf , verif };
    cout << "nouvelle inter : (" << position[0] << "," << position[1] << ") " << position[2] << "\n";
    return position;
}

/* Calcul de la moyenne des coordonnées des intersections.
Prend en entrée un vecteur à deux dimensions comportant toutes les coordonnées des points
dont on veut calculer la moyenne et ressort un vecteur avec les coordonnées x,y moyenne*/
vector<double> Code_distance::moyenne_coord(vector<vector<double>> coordonnees) {
    size_t length = coordonnees.size();
    double total_x = 0;
    double total_y = 0;
    // Pour chaque élément du vecteur d'entrée, on ajoute la valeur de la coordonnée correspondante
    for (int i = 0; i < length; i++) {
        if (coordonnees[i][2] == 0) {
            // Si l'intersection a une verif a 0, on ne l'ajoute pas dans la moyenne
            length = length-1;
        }
        else {
            total_x += coordonnees[i][0];
            total_y += coordonnees[i][1];
        }
    }
    // On fait la moyenne des coordonées
    total_x = total_x / length;
    total_y = total_y / length;
    std::vector<double> total = { total_x, total_y };
    // Affiche le résultat qui correspond aux coordonnées de l'asset
    //qDebug() << "[*] Coordonnées de l'asset : (" << total[0] << "," << total[1] << ")\n";
    return total;
}

/* Ce code permet de transformer les droites en demi droite.
Puisqu'on sait la direction dans laquelle un locator détecte un asset, on supprime les intersections
qui sont détéctées à l'inverse de cette direction.
Prend un array contenant les informations d'une intersection et des deux locators qui la génère
Rend un double qui est soit 1 soit 0 pour dire si l'intersection est dans la bonne direction (1 = oui)*/
double Code_distance::quarter_verif(vector<double> intersection) {
    bool verif1 = false;
    bool verif2 = false;
    if (intersection[4] < 0) {
        intersection[4] = 360 + intersection[4];
    }
    if (intersection[7] < 0) {
        intersection[7] = 360 + intersection[7];
    }

    if (0 < intersection[4] && intersection[4] < 90) {
        if (intersection[2] <= intersection[0] && intersection[3] <= intersection[1]) {
            verif1 = true;
        }
    }
    if (90 < intersection[4] && intersection[4] < 180) {
        if (intersection[2] >= intersection[0] && intersection[3] <= intersection[1]) {
            verif1 = true;
        }
    }
    if (180 < intersection[4] && intersection[4] < 270) {
        if (intersection[2] >= intersection[0] && intersection[3] >= intersection[1]) {
            verif1 = true;
        }
    }
    if (270 < intersection[4] && intersection[4] < 360) {
        if (intersection[2] <= intersection[0] && intersection[3] >= intersection[1]) {
            verif1 = true;
        }
    }

    if (0 < intersection[7] && intersection[7] < 90) {
        if (intersection[5] <= intersection[0] && intersection[6] <= intersection[1]) {
            verif2 = true;
        }
    }
    if (90 < intersection[7] && intersection[7] < 180) {
        if (intersection[5] >= intersection[0] && intersection[6] <= intersection[1]) {
            verif2 = true;
        }
    }
    if (180 < intersection[7] && intersection[7] < 270) {
        if (intersection[5] >= intersection[0] && intersection[6] >= intersection[1]) {
            verif2 = true;
        }
    }
    if (270 < intersection[7] && intersection[7] < 360) {
        if (intersection[5] <= intersection[0] && intersection[6] >= intersection[1]) {
            verif2 = true;
        }
    }

    // On vérifie que la direction est bonne pour les deux locators
    if (verif1 == true && verif2 == true) {
        return 1;
    }
    else {
        return 0;
    }
}


/* Calcul la distance entre tous les points
Prend en entrée un vecteur avec les toutes les coordonnées (x, y) des intersections
Sort un aray à deux dimensions avec la liste des distances entre les points
exemple: la valeur en [0][5] est la distance entre le point 0 et 5 */
vector<vector<double>> Code_distance::distance(vector<vector<double>> coordonnees) {
    std::vector<vector<double>> table_distance;
    size_t length = coordonnees.size();
    for (int i = 0; i < length; i++) {
        // On crée la ligne avec toutes les distances entre le point i et les autres
        std::vector<double> ligne;
        for (int j = 0; j < length; j++) {
            // Calcul de la distance entre le point i et j
            double dist = sqrt((pow((coordonnees[j][0]-coordonnees[i][0]), 2)) +
                (pow((coordonnees[j][1] - coordonnees[i][1]), 2)));
            // On ajoute la valeur à la ligne
            ligne.push_back(dist);
        }
        // On ajoute la ligne au tableau
        table_distance.push_back(ligne);
    }
    // On return le vecteur à deux dimensions
    return table_distance;
}


/* Fonction qui cherche un point de référence, celui qui est en moyenne le moins loin des autres
Prend en entrée un vecteur à deux dimensions comportant toutes les distances entre chaque points
Sort un int correspondant à l'index de l'intersection de référence
*/
__int64 Code_distance::point_moyen(vector<vector<double>> distances) {
    std::vector<double> moyennes;
    size_t length = distances.size();
    double moyenne;
    for (int i = 0; i < length; i++) {
        moyenne = 0;
        size_t llength = distances.size();
        for (int j = 0; j < llength; j++) {
            moyenne += distances[i][j];
        }
        moyenne /= (length - 1);
        moyennes.push_back(moyenne);
    }
    return std::min_element(moyennes.begin(), moyennes.end()) - moyennes.begin();
}

/* Cherche tous les points qui sont dans un rayon défini autout du poit de référence
Prend en entrée un vecteur avec les distances entre le point de référence et les autres
et un double qui est la distance à partir de laquelle un point n'est plus considéré comme un voisin
Sort un vecteur avec l'index de chaque intersection voisine */
vector<int> Code_distance::voisins(vector<double> distances, double tolerance) {
    std::vector<int> id_voisins;
    size_t length = distances.size();
    for (int i = 0; i < length; i++) {
        if (distances[i] <= tolerance) {
            // Si la distance est inférieure à la tolérance, on ajoute l'index au vecteur
            id_voisins.push_back(i);
        }
    }
    return id_voisins;
}

/* Fonction principal : renvoie les coordonnées estimées de l'asset à partir des data des locators
Prend en entrée un vecteur à deux dimensions avec les couples de positions {x, y} de chaque locator
Sort un vecteur avec la position {x, y} calculée de l'asset.
*/

vector<double> Code_distance::asset_position(std::vector<vector<double>> data_locator) {
    std::vector<vector<double>> coord_intersections;
    std::vector<int> invalid_data;
    std::vector<vector<double>> table_distance;
    std::vector<double> resultat = {0, 0};
    size_t nombre_locator = data_locator.size();

    /* Ce code permet de vérifier que chaque locator a des données.
    Si un locator n'en a pas, on ajoute son index au vecteur invalid_data */
    for (int i = 0; i < nombre_locator; i++) {

        if (data_locator[i][0] == NULL && data_locator[i][1] == NULL && data_locator[i][2] == NULL) {
            invalid_data.push_back(i);
        }
    }
    // On enlève de data_locator tous les locators sans angle entrés dans invalid_data
    std::reverse(invalid_data.begin(), invalid_data.end());
    for (int i = 0; i < invalid_data.size(); i++) {
        //qDebug() << "[*] Les données du locator " << invalid_data[i] << " ne sont pas valides.\n";
        data_locator.erase(data_locator.begin() + invalid_data[i]);
    }
    // Il ne resque que les locators avec un angle valide, on change le nombre de locator
    nombre_locator = data_locator.size();

    // S'il n'y a que deux locators, il n'y a pas besoin de process le résultat puisqu'il n'y a qu'une intersection
    if (nombre_locator >= 3) {
        // On calcul toutes les intersections à l'aide des datas entrées pour chaque locator
        for (int i = 0; i < nombre_locator - 1; i++) {
            for (int j = i + 1; j < nombre_locator; j++) {
                std::vector<double> new_intersection = intersection(
                    data_locator[i][0], data_locator[i][1], data_locator[i][2],
                    data_locator[j][0], data_locator[j][1], data_locator[j][2]);
                coord_intersections.push_back(new_intersection);
            }
        }
        // On récupère toutes les distances entre chaque intersection
        table_distance = distance(coord_intersections);
        double tolerance = 1.5;
        // On récupère un vecteur avec es distances entre le point de référence et les autres
        std::vector<double> distances_point_reference = table_distance[point_moyen(table_distance)];
        size_t length = distances_point_reference.size();
        /* On calcul la tolérance en faisant la moyenne de toutes les distances du point de référence
        On ne prend pas en compte le point le plus éloigné car ce point créer souvent beaucoup d'erreur */
        for (int i = 0; i < length; i++) {
            if (distances_point_reference[i] != *std::max_element(distances_point_reference.begin(), distances_point_reference.end()) && distances_point_reference[i] != 0) {
               // tolerance += distances_point_reference[i];
            }
        }
        /* On divise le total par le nombre de distances utilisées -2 pour ne pas compter
        la distance avec lui même et la distance avec le point le plus éloigné*/
        //tolerance /= coord_intersections.size() - 2;
        // Plus la tolérance est basse, moins il y a fd'erreur
        //qDebug() << "Erreur : " << tolerance << " m\n";
        std::vector<vector<double>> coordonnees_finale;
        // On récupère une liste des points voisins
        std::vector<int> points_voisins = voisins(table_distance[point_moyen(table_distance)], tolerance*1.5);
        for (int i = 0; i < points_voisins.size(); i++) {
            // On ajoute au vecteur coord_finale toutes les coordonnées des intersections gardées
            coordonnees_finale.push_back(coord_intersections[points_voisins[i]]);
        }
        // On fait la moyenne des coordonnées des intersections gardées
        std::vector<double> resultat = moyenne_coord(coordonnees_finale);
    }
    // S'il y 1 un ou 0 locator, il n'y a pas d'intersection
     if (nombre_locator == 1 || nombre_locator == 0) {
        //qDebug() << "Nombre de locator insuffisant !";
        resultat = { 1,1 };
    }
    // S'il n'y a que deux locator, on affiche les coordonnées de la seule intersection
    else {
        // On calcul toutes les intersections à l'aide des datas entrées pour chaque locator
        for (int i = 0; i < nombre_locator - 1; i++) {
            for (int j = i + 1; j < nombre_locator; j++) {
                std::vector<double> new_intersection = intersection(
                    data_locator[i][0], data_locator[i][1], data_locator[i][2],
                    data_locator[j][0], data_locator[j][1], data_locator[j][2]);
                coord_intersections.push_back(new_intersection);
            }
        }
        resultat = moyenne_coord(coord_intersections);
        //qDebug() << "Calcul de l'erreur impossible avec 2 locators";
    }
    //qDebug()<<"position trouvé"<<resultat[1]<<" "<<resultat[2];
    return resultat;
}
