using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DevelopingTheGamesAssembly.StudioTheGame
{
    class PublishedGame
    {
        public PublishedGame(Project aProject)
        {
            myName = aProject.ProjectName;
            myQuality = (int)((float)aProject.Difficulty * aProject.Progress);
            myPopularity = myQuality * 10;
        }

        public void DecreasePopularity()
        {
            myPopularity -= (10.0f / (float)(myQuality));
        }

        public int PayOut
        {
            get
            {
                int payout = myQuality * (int)myPopularity;
                if (payout > 0)
                {
                    return payout;
                }
                return 0;
            }
        }

        public string GetName
        {
            get
            {
                return myName;
            }
        }
        
        public float Popularity
        {
            get
            {
                return myPopularity;
            }
        } 

        private string myName;
        private float myPopularity;
        private int myQuality;
    }
}
