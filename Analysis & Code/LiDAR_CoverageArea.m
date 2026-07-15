%% ========================================================================
%  LiDAR Scan Coverage Simulation
%
%  Description:
%      Simulates the scan path of a rotating LiDAR sensor mounted on a
%      secondary rotating axis and projects the resulting coverage onto
%      a spherical surface.
%
%  Developed by:
%      Jacob Ondo
%
%  Based on methodology developed in collaboration with:
%      Wyatt Gay
%
%  Date:
%      February 2026
%% ========================================================================

clear
clc
close all

%% ========================================================================
%  Sphere Definition
%  ========================================================================

R = 100;                     % Sphere radius

[X,Y,Z] = sphere;
X = X * R;
Y = Y * R;
Z = Z * R;

%% ========================================================================
%  LiDAR Parameters
%  ========================================================================

freq_Li  = 10;               % LiDAR scan frequency [Hz]
freq_mot = 3;                % Secondary axis frequency [Hz]

omega_Li  = 2*pi*freq_Li;    % LiDAR angular velocity [rad/s]
omega_mot = 2*pi*freq_mot;   % Motor angular velocity [rad/s]

duration = 1;                % Simulation duration [s]
dt       = 0.001;            % Time step [s]
t        = 0:dt:duration;

%% ========================================================================
%  Initial Ray Definitions
%  ========================================================================

V_Li    = [1;0;0];

V_Band1 = [.9239;.3827;0];
V_Band2 = [.9239;-.3827;0];

vectors_center = zeros(3,length(t));

%% ========================================================================
%  Generate LiDAR Scan Path
%  ========================================================================

for k = 1:length(t)

    Theta_Li = omega_Li * t(k);

    Rot_y = [ cos(Theta_Li)   0   sin(Theta_Li)
                     0         1         0
             -sin(Theta_Li)   0   cos(Theta_Li)];

    Theta_mot = omega_mot * t(k);

    Rot_z = [ cos(Theta_mot)  -sin(Theta_mot)   0
              sin(Theta_mot)   cos(Theta_mot)   0
                     0                0          1];

    vectors_center(:,k) = Rot_z * Rot_y * V_Li;

end

%% ========================================================================
%  Project Scan Path onto Sphere
%  ========================================================================

vectors_projected = zeros(3,length(t));

for k = 1:length(t)

    vectors_projected(:,k) = ...
        vectors_center(:,k) / norm(vectors_center(:,k));

end

%% ========================================================================
%  Compute LiDAR Coverage Band (±22.5°)
%  ========================================================================

alpha = deg2rad(22.5);

U = vectors_projected;
N = size(U,2);

% Tangent approximation

dU = zeros(3,N);

dU(:,2:N-1) = (U(:,3:N)-U(:,1:N-2))/(2*dt);
dU(:,1)     = (U(:,2)-U(:,1))/dt;
dU(:,N)     = (U(:,N)-U(:,N-1))/dt;

% Tangent vector

T = dU - U .* sum(U.*dU,1);
T = T ./ vecnorm(T);

% Surface normal

S = cross(U,T,1);
S = S ./ vecnorm(S);

% Rodrigues rotation

U_plus  = U*cos(alpha) ...
         + cross(T,U,1)*sin(alpha) ...
         + T.*sum(T.*U,1)*(1-cos(alpha));

U_minus = U*cos(alpha) ...
         - cross(T,U,1)*sin(alpha) ...
         + T.*sum(T.*U,1)*(1-cos(alpha));

%% ========================================================================
%  User Display Selection
%  ========================================================================

choice = 0;

while ~ismember(choice,[1 2])

    choice = input( ...
        'Enter 1 for LiDAR Path or 2 for Band Coverage: ');

    if ~ismember(choice,[1 2])

        fprintf('\nInvalid selection.\n\n');

    end

end

%% ========================================================================
%  Generate Surface Data
%  ========================================================================

if choice == 1

    X_Li = R*[vectors_projected(1,:); vectors_projected(1,:)];
    Y_Li = R*[vectors_projected(2,:); vectors_projected(2,:)];
    Z_Li = R*[vectors_projected(3,:); vectors_projected(3,:)];

else

    X_band = R*[U_plus(1,:); vectors_projected(1,:); U_minus(1,:)];
    Y_band = R*[U_plus(2,:); vectors_projected(2,:); U_minus(2,:)];
    Z_band = R*[U_plus(3,:); vectors_projected(3,:); U_minus(3,:)];

end

%% ========================================================================
%  Visualization
%  ========================================================================

figure
hold on

surf(X,Y,Z,...
    'FaceColor','white',...
    'EdgeColor','white',...
    'FaceAlpha',0.2,...
    'EdgeAlpha',0.2);

if choice == 1

    surf(X_Li,Y_Li,Z_Li,...
        'FaceColor','red',...
        'EdgeColor','red');

else

    surf(X_band,Y_band,Z_band,...
        'FaceColor','interp',...
        'EdgeColor','blue',...
        'FaceAlpha',0.6,...
        'EdgeAlpha',0.6);

end

view(45,30)
axis equal
grid on