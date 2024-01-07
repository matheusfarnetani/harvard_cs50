document.addEventListener('DOMContentLoaded', function () {

    // Function to handle form submission
    function handleSubmit(event) {
        event.preventDefault(); // Prevent the default form submission behavior

        // Get form input values
        const firstName = document.getElementById('first-name').value;
        const lastName = document.getElementById('last-name').value;
        const email = document.getElementById('input-email').value;
        const phone = document.getElementById('input-phone').value;
        const bestTime = document.getElementById('input-time').value;
        const additionalInfo = document.getElementById('input-info').value;

        // Print into console
        console.log('Form submitted:', {
            firstName,
            lastName,
            email,
            phone,
            bestTime,
            additionalInfo
        });

        alert('This website doens\'t have a host, so it can\'t save your info.\nPlease send an email to matheusfarnetani@gmail.com.\nThanks.');
    }

    // Attach the submit event listener to the form
    const contactForm = document.getElementById('contact-form');
    contactForm.addEventListener('submit', handleSubmit);
});