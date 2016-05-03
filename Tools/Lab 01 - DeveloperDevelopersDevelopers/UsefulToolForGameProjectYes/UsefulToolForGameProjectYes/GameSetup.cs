using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UsefulToolForGameProjectYes
{
    public class GameSetup
    {
        public GameSetup()
        {
            myResolution = new Resolution(1920, 1080);

            myIsFullscreen = false;
            mySkipIntro = true;
            mySkipSplashscreen = true;
            myMuteAllSounds = true;
        }

        #region Properties

        public Resolution ResolutoinSettings
        {
            get
            {
                return myResolution;
            }
            set
            {
                myResolution = value;
            }
        }

        public bool SkipIntro
        {
            get
            {
                return mySkipIntro;
            }
            set
            {
                mySkipIntro = value;
            }
        }
        public bool IsFullscreen
        {
            get
            {
                return myIsFullscreen;
            }
            set
            {
                myIsFullscreen = value;
            }
        }
        public bool SkipSplashscreen
        {
            get
            {
                return mySkipSplashscreen;
            }
            set
            {
                mySkipSplashscreen = value;
            }
        }
        public bool MuteAllSounds
        {
            get
            {
                return myMuteAllSounds;
            }
            set
            {
                myMuteAllSounds = value;
            }
        }
        #endregion

        private Resolution myResolution;
        private bool myIsFullscreen;
        private bool mySkipIntro;
        private bool mySkipSplashscreen;
        private bool myMuteAllSounds;
    }
}
