#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CORNERS 1000
#define MAX_CONNECTIONS 10000
#define INF INT_MAX

typedef struct
{
    int origin;
    int destination;
    int time;
} Street;

typedef struct
{
    int times[MAX_CORNERS];
    int previous[MAX_CORNERS];
    int visited[MAX_CORNERS];
} RouteInfo;

void initRouteInfo(RouteInfo *info, int num_corners)
{
    for (int i = 0; i <= num_corners; i++)
    {
        info->times[i] = INF;
        info->previous[i] = -1;
        info->visited[i] = 0;
    }

    // Set initial corner (firefighter station) to 0 time
    info->times[1] = 0;
}

// Function to find the unvisited corner with minimum time
int findMinTimeCorner(RouteInfo *info, int num_corners)
{
    int min_time = INF;
    int min_corner = -1;

    for (int i = 1; i <= num_corners; i++)
    {
        if (!info->visited[i] && info->times[i] < min_time)
        {
            min_time = info->times[i];
            min_corner = i;
        }
    }

    return min_corner;
}

void findFastestRoute(Street *streets, int num_streets, RouteInfo *info, int num_corners)
{
    for (int i = 1; i <= num_corners; i++)
    {
        // Find corner with minimum time
        int current_corner = findMinTimeCorner(info, num_corners);
        if (current_corner == -1)
            break; // No more reachable corners

        info->visited[current_corner] = 1;

        // Update times for all connected corners
        for (int j = 0; j < num_streets; j++)
        {
            if (streets[j].origin == current_corner)
            {
                int next_corner = streets[j].destination;
                int travel_time = streets[j].time;

                if (!info->visited[next_corner] &&
                    info->times[current_corner] != INF &&
                    info->times[current_corner] + travel_time < info->times[next_corner])
                {
                    info->times[next_corner] = info->times[current_corner] + travel_time;
                    info->previous[next_corner] = current_corner;
                }
            }
        }
    }
}

void printRoute(RouteInfo *info, int fire_location)
{
    if (info->times[fire_location] == INF)
    {
        printf("No possible route to corner #%d\n", fire_location);
        return;
    }

    int path[MAX_CORNERS];
    int path_size = 0;

    // Reconstruct the path from destination to source
    for (int corner = fire_location; corner != -1; corner = info->previous[corner])
    {
        path[path_size++] = corner;
    }

    // Print the path in correct order (source to destination) inverting "path"
    printf("route to corner #%d:", fire_location);
    for (int i = path_size - 1; i >= 0; i--)
    {
        printf(" %d", path[i]);
    }
    printf("\ncalculated time for route = %d min.\n", info->times[fire_location]);
}

int main(void)
{
    FILE *file = fopen("bombeiro.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int fire_location, num_corners;
    fscanf(file, "%d", &fire_location);
    fscanf(file, "%d", &num_corners);

    Street streets[MAX_CONNECTIONS];
    int num_streets = 0;

    // Read street connections
    int origin, destination, time;
    while (1)
    {
        fscanf(file, "%d", &origin);
        if (origin == 0)
            break;

        fscanf(file, "%d %d", &destination, &time);

        streets[num_streets].origin = origin;
        streets[num_streets].destination = destination;
        streets[num_streets].time = time;
        num_streets++;
    }

    fclose(file);

    RouteInfo route_info;
    initRouteInfo(&route_info, num_corners);
    findFastestRoute(streets, num_streets, &route_info, num_corners);

    printRoute(&route_info, fire_location);

    return 0;
}