#include <bits/stdc++.h>
#define MAX 50
#define MAX_VAL 100
#define TOTAL 50

double dp[MAX][MAX];

typedef struct
{
  int x;
  int y;
} Vertex;

typedef struct
{
  int total_vertices;
  Vertex vertices[MAX];
} Polygon;

typedef struct
{
  int i;
  int j;
  double length;
} Diagonal;

double min(double a, double b)
{
  return (a < b) ? a : b;
}

Vertex generateVertex()
{
  Vertex v;
  v.x = rand() % MAX_VAL;
  v.y = rand() % MAX_VAL;
  return v;
}

double dist(Vertex v1, Vertex v2)
{
  return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

int crossProduct(Vertex v1, Vertex v2)
{
  return v1.x * v2.y - v1.y * v2.x;
}

int isConvex(Polygon poly)
{
  int n = poly.total_vertices;
  int crossproduct = 0;
  for (int i = 0; i < n; i++)
  {
    Vertex v1 = poly.vertices[i];
    Vertex v2 = poly.vertices[(i + 1) % n];
    Vertex v3 = poly.vertices[(i + 2) % n];
    int cp = crossProduct((Vertex){v2.x - v1.x, v2.y - v1.y}, (Vertex){v3.x - v2.x, v3.y - v2.y});
    if (i == 0)
    {
      crossproduct = cp;
    }
    else if (crossproduct * cp < 0)
    {
      return 0;
    }
  }
  return 1;
}

int cmp_diag(const void *u, const void *v)
{
  Diagonal *du = (Diagonal *)u;
  Diagonal *dv = (Diagonal *)v;
  return (du->length < dv->length) ? 1 : -1;
}

int cmp(const void *a, const void *b)
{
  Vertex *p1 = (Vertex *)a;
  Vertex *p2 = (Vertex *)b;
  return (p1->x - p2->x);
}

int intersects(Vertex a, Vertex b, Vertex c, Vertex d)
{
  int d1 = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  int d2 = (b.x - a.x) * (d.y - a.y) - (d.x - a.x) * (b.y - a.y);
  int d3 = (d.x - c.x) * (a.y - c.y) - (a.x - c.x) * (d.y - c.y);
  int d4 = (d.x - c.x) * (b.y - c.y) - (b.x - c.x) * (d.y - c.y);
  return (d1 * d2 < 0) && (d3 * d4 < 0);
}

int orientation(Vertex v1, Vertex v2, Vertex v3)
{
  int res = (v2.y - v1.y) * (v3.x - v2.x) - (v2.x - v1.x) * (v3.y - v2.y);
  if (res == 0)
  {
    return 0;
  }
  return (res > 0) ? 1 : 2;
}

void sort_vertices(Vertex *points, int n)
{
  int leftmost = 0;
  for (int i = 1; i < n; i++)
  {
    if (points[i].x < points[leftmost].x)
    {
      leftmost = i;
    }
  }
  Vertex temp = points[0];
  points[0] = points[leftmost];
  points[leftmost] = temp;

  qsort(points + 1, n - 1, sizeof(Vertex), cmp);
  int ct = 1;
}

Polygon generatePolygon(int n)
{
  Polygon P;
  P.total_vertices = n;
  Vertex *arr = new Vertex[n];
  arr[0] = generateVertex();
  for (int i = 1; i < n; i++)
  {
    Vertex v;
    do
    {
      v = generateVertex();
    } while (!isConvex((Polygon){i, *arr}));
    arr[i] = v;
  }
  for (int i = 0; i < n; i++)
  {
    P.vertices[i] = arr[i];
  }
  return P;
}

double cost(Vertex *points, int i, int j, int k)
{
  Vertex v1 = points[i];
  Vertex v2 = points[j];
  Vertex v3 = points[k];
  return dist(v1, v2) + dist(v2, v3) + dist(v3, v1);
}

double minTriangulationCostDP(Vertex *points, int n)
{
  double Max = 1e7;
  if (n <= 2)
  {
    return 0;
  }

  for (int m = 0; m < n; m++)
  {
    for (int i = 0, j = m; i < n; i++, j++)
    {
      if (j <= i + 1)
      {
        dp[i][j] = 0.0;
      }
      else
      {
        dp[i][j] = Max;
        for (int k = i + 1; k < j; k++)
        {
          double ans = dp[i][k] + dp[k][j] + cost(points, i, j, k);
          dp[i][j] = min(dp[i][j], ans);
        }
      }
    }
  }
  return dp[0][n - 1];
}

double minTriangulationCostGreedy(Vertex *points, int n)
{
  Diagonal arr[MAX * MAX];
  int taken[MAX][MAX] = {0};
  int count_diag = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 2; j <= n - 2; j++)
    {
      if (!taken[i][j] && !taken[j][i])
      {
        taken[i][j] = 1;
        taken[j][i] = 1;
        double len = dist(points[i], points[j]);
        arr[count_diag].i = i;
        arr[count_diag].j = j;
        arr[count_diag].length = len;
        count_diag++;
      }
    }
  }
  qsort(arr, count_diag, sizeof(Diagonal), cmp_diag);

  int visited[MAX][MAX] = {0};
  double diag_cost = 0;
  int count = 0;
  for (int k = 0; k < count_diag; k++)
  {
    Diagonal diag = arr[k];
    if (!visited[diag.i][diag.j] && !intersects(points[diag.i], points[diag.j], points[(diag.i + 1) % n], points[(diag.j + 1) % n]) && count <= n - 3)
    {
      visited[diag.i][diag.j] = 1;
      diag_cost += diag.length;
      count++;
    }
  }
  double side_cost = 0;
  for (int i = 0; i < n; i++)
  {
    int j = (i + 1) % n;
    side_cost += dist(points[i], points[j]);
  }
  return diag_cost + side_cost;
}
int main()
{
  srand(time(0));
  double minCostGreedy, minCostDP;
  FILE *fout = fopen("dpobsfirst.txt", "w");
  FILE *fout1 = fopen("greedyobs.txt", "w");
  FILE *fnew = fopen("newobs.txt", "w");
  FILE *fp1 = fopen("dpfirstres.txt", "w");
  FILE *fp2 = fopen("grdyres.txt", "w");
  FILE *fdev = fopen("deviations.txt", "w");
  fprintf(fout, "Vertices,Avg.Time Taken\n");
  fprintf(fout1, "Vertices,Avg.Time Taken\n");
  fprintf(fnew, "Vertices, Avg.Time Taken DP, Avg.Time Taken Greedy\n");
  for (int i = 3; i <= MAX; i++)
  {
    float time_sum = 0, time_sum1 = 0;
    printf("\nNumber of Vertices:%d\n", i);
    for (int j = 0; j < TOTAL; j++)
    {
      Polygon poly;
      do
      {
        poly = generatePolygon(i);
      } while (!isConvex(poly));
      sort_vertices(poly.vertices, poly.total_vertices);
      Vertex points[i];
      fprintf(fp1, "Number of Vertices: %d\n", poly.total_vertices);
      fprintf(fp2, "Number of Vertices:%d\n", poly.total_vertices);
      fprintf(fdev, "Number of Vertices:%d\n", poly.total_vertices);
      for (int k = 0; k < poly.total_vertices; k++)
      {
        points[k].x = poly.vertices[k].x;
        points[k].y = poly.vertices[k].y;
        fprintf(fp1, "%d,%d\n", poly.vertices[k].x, poly.vertices[k].y);
        fprintf(fp2, "%d,%d\n", poly.vertices[k].x, poly.vertices[k].y);
      }
      float start1 = clock();
      minCostGreedy = minTriangulationCostGreedy(points, i);
      float end1 = clock();
      fprintf(fp2, "Cost of Triangulation is %f\n", minCostGreedy);
      float start = clock();
      minCostDP = minTriangulationCostDP(points, i);
      fprintf(fp2, "Cost of Triangulation (DP) is %f\n", minCostDP);
      float end = clock();
      fprintf(fdev, "%f\n", minCostDP - minCostGreedy);
      fprintf(fp1, "Cost of Triangulation is %f\n", minCostDP);
      float time_req = (end - start) * 1000 / CLOCKS_PER_SEC;
      float time_req1 = (end1 - start1) * 1000 / CLOCKS_PER_SEC;
      printf("Time taken for round %d using DP is %0.4fms\n", j + 1, time_req);
      printf("Time taken for round %d using Greedy is %0.4fms\n", j + 1, time_req1);
      time_sum += time_req;
      time_sum1 += time_req1;
      fprintf(fp1, "\n");
      fprintf(fp2, "\n");
    }
    fprintf(fout1, "%d,%0.4f\n", i, time_sum1 / TOTAL);
    fprintf(fout, "%d,%0.4f\n", i, time_sum / TOTAL);
    fprintf(fnew, "%d,%0.4f,%0.4f\n", i, time_sum / TOTAL, time_sum1 / TOTAL);
  }
  printf("\nFiles have been generated successfully\n");
  fclose(fp1);
  fclose(fp2);
  fclose(fout1);
  fclose(fout);
  fclose(fdev);
  return 0;
}