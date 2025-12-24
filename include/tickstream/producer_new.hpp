namespace tickstream
{

    // Base interface for all stochastic processes
    class IProcess
    {
    public:
        virtual ~IProcess() = default;
        virtual double next(double dt, std::mt19937_64 &rng) = 0;
        virtual void reset(double initial_value) = 0;
        virtual std::unique_ptr<IProcess> clone() const = 0;
    };

    // Geometric Brownian Motion (Black-Scholes)
    class GBM : public IProcess
    {
    public:
        struct Config
        {
            double initial_price = 100.0;
            double mu = 0.05;   // Annual drift
            double sigma = 0.2; // Annual volatility
            double risk_free_rate = 0.02;
        };

        GBM(Config config);
        // ... implementation
    };

    // Ornstein-Uhlenbeck (Mean-reverting)
    class OU : public IProcess
    {
    public:
        struct Config
        {
            double initial_price = 100.0;
            double mean = 100.0; // Long-term mean
            double theta = 0.1;  // Mean reversion speed
            double sigma = 0.2;  // Volatility
        };
        // ... implementation
    };

    // Merton Jump Diffusion
    class MertonJump : public IProcess
    {
    public:
        struct Config
        {
            double initial_price = 100.0;
            double mu = 0.05;
            double sigma = 0.2;
            double jump_lambda = 0.1; // Jump frequency
            double jump_mu = -0.02;   // Jump mean
            double jump_sigma = 0.05; // Jump volatility
        };
        // ... implementation
    };
} // namespace tickstream::process