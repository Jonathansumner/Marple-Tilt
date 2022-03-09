namespace MarpleTilt {
    class BaseState {
        public:
            BaseState() {}
            virtual ~BaseState() {}

            virtual void OnEntry() = 0;
            virtual void OnExit() = 0;

            virtual void Update() = 0;
    };
}